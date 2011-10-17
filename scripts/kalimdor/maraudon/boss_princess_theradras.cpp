/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Princess_Theradras
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "precompiled.h"

#define SPELL_DUSTFIELD             21909
#define SPELL_BOULDER               21832
#define SPELL_THRASH                3391
#define SPELL_REPULSIVEGAZE         21869

struct MANGOS_DLL_DECL boss_ptheradrasAI : public ScriptedAI
{
    boss_ptheradrasAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 Dustfield_Timer;
    uint32 Boulder_Timer;
    uint32 Thrash_Timer;
    uint32 RepulsiveGaze_Timer;

    void Reset()
    {
        Dustfield_Timer = 8000;
        Boulder_Timer = 2000;
        Thrash_Timer = 5000;
        RepulsiveGaze_Timer = 23000;
    }

    void JustDied(Unit* Killer)
    {
        m_creature->SummonCreature(12238,28.067f, 61.875f, -123.405f, 4.67f, TEMPSUMMON_TIMED_DESPAWN, 600000);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Dustfield_Timer
        if (Dustfield_Timer < diff)
        {
            DoCastSpellIfCan(m_creature,SPELL_DUSTFIELD);
            Dustfield_Timer = 14000;
        }else Dustfield_Timer -= diff;

        //Boulder_Timer
        if (Boulder_Timer < diff)
        {
            Unit* target = NULL;
            target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
            if (target)
                DoCastSpellIfCan(target,SPELL_BOULDER);
            Boulder_Timer = 10000;
        }else Boulder_Timer -= diff;

        //RepulsiveGaze_Timer
        if (RepulsiveGaze_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_REPULSIVEGAZE);
            RepulsiveGaze_Timer = 20000;
        }else RepulsiveGaze_Timer -= diff;

        //Thrash_Timer
        if (Thrash_Timer < diff)
        {
            DoCastSpellIfCan(m_creature,SPELL_THRASH);
            Thrash_Timer = 18000;
        }else Thrash_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_ptheradras(Creature* pCreature)
{
    return new boss_ptheradrasAI(pCreature);
}

void AddSC_boss_ptheradras()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_princess_theradras";
    pNewScript->GetAI = &GetAI_boss_ptheradras;
    pNewScript->RegisterSelf();
}
