#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dwLineID; } ;
struct TYPE_11__ {TYPE_1__* Lines; scalar_t__ hmx; } ;
struct TYPE_10__ {TYPE_5__ Info; struct TYPE_10__* Next; } ;
struct TYPE_9__ {scalar_t__ DisplayControls; TYPE_2__* Connections; TYPE_5__ Info; struct TYPE_9__* Next; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSND_MIXER_DESTINATION ;
typedef  TYPE_2__* PSND_MIXER_CONNECTION ;
typedef  TYPE_3__* PSND_MIXER ;
typedef  int /*<<< orphan*/  (* PFNSNDMIXENUMCONNECTIONS ) (TYPE_3__*,scalar_t__,TYPE_5__*,int /*<<< orphan*/ ) ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
SndMixerEnumConnections(PSND_MIXER Mixer,
                        DWORD LineID,
                        PFNSNDMIXENUMCONNECTIONS EnumProc,
                        PVOID Context)
{
    if (Mixer->hmx)
    {
        PSND_MIXER_DESTINATION Line;

        for (Line = Mixer->Lines; Line != NULL; Line = Line->Next)
        {
            if (Line->Info.dwLineID == LineID)
            {
                PSND_MIXER_CONNECTION Connection;

                if (Line->DisplayControls != 0)
                {
                    if (!EnumProc(Mixer,
                                  LineID,
                                  &Line->Info,
                                  Context))
                    {
                        return FALSE;
                    }
                }

                for (Connection = Line->Connections; Connection != NULL; Connection = Connection->Next)
                {
                    if (!EnumProc(Mixer,
                                  LineID,
                                  &Connection->Info,
                                  Context))
                    {
                        return FALSE;
                    }
                }

                return TRUE;
            }
        }
    }

    return FALSE;
}