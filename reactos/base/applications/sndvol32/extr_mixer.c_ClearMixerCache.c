#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {TYPE_1__* Lines; } ;
struct TYPE_6__ {struct TYPE_6__* Next; struct TYPE_6__* Controls; struct TYPE_6__* Connections; } ;
typedef  TYPE_1__* PSND_MIXER_DESTINATION ;
typedef  TYPE_1__* PSND_MIXER_CONNECTION ;
typedef  TYPE_3__* PSND_MIXER ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static VOID
ClearMixerCache(PSND_MIXER Mixer)
{
    PSND_MIXER_DESTINATION Line, NextLine;
    PSND_MIXER_CONNECTION Con, NextCon;

    for (Line = Mixer->Lines; Line != NULL; Line = NextLine)
    {
        if (Line->Controls != NULL)
        {
            HeapFree(GetProcessHeap(),
                     0,
                     Line->Controls);
        }

        for (Con = Line->Connections; Con != NULL; Con = NextCon)
        {
            if (Con->Controls != NULL)
            {
                HeapFree(GetProcessHeap(),
                         0,
                         Con->Controls);
            }

            NextCon = Con->Next;
            HeapFree(GetProcessHeap(),
                     0,
                     Con);
        }

        NextLine = Line->Next;
        HeapFree(GetProcessHeap(),
                 0,
                 Line);
    }
    Mixer->Lines = NULL;
}