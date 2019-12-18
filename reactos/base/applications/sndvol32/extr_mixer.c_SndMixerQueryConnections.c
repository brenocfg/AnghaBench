#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int cbStruct; scalar_t__ szName; scalar_t__ dwSource; int /*<<< orphan*/  dwDestination; } ;
struct TYPE_15__ {scalar_t__ hmx; } ;
struct TYPE_12__ {scalar_t__ cConnections; int /*<<< orphan*/  dwDestination; } ;
struct TYPE_14__ {TYPE_2__* Connections; TYPE_1__ Info; } ;
struct TYPE_13__ {struct TYPE_13__* Next; scalar_t__ DisplayControls; int /*<<< orphan*/ * Controls; TYPE_6__ Info; } ;
typedef  TYPE_2__ SND_MIXER_CONNECTION ;
typedef  TYPE_3__* PSND_MIXER_DESTINATION ;
typedef  TYPE_2__* PSND_MIXER_CONNECTION ;
typedef  TYPE_5__* PSND_MIXER ;
typedef  scalar_t__ MMRESULT ;
typedef  TYPE_6__ MIXERLINE ;
typedef  int /*<<< orphan*/  LineInfo ;
typedef  int /*<<< orphan*/ * LPMIXERCONTROL ;
typedef  int /*<<< orphan*/  HMIXEROBJ ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIXER_GETLINEINFOF_SOURCE ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  SndMixerQueryControls (TYPE_5__*,scalar_t__*,TYPE_6__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mixerGetLineInfo (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
SndMixerQueryConnections(PSND_MIXER Mixer,
                         PSND_MIXER_DESTINATION Line)
{
    UINT i, DispControls;
    MIXERLINE LineInfo;
    MMRESULT Result;
    BOOL Ret = TRUE;

    LineInfo.cbStruct = sizeof(LineInfo);
    for (i = Line->Info.cConnections; i > 0; i--)
    {
        LineInfo.dwDestination = Line->Info.dwDestination;
        LineInfo.dwSource = i - 1;
        Result = mixerGetLineInfo((HMIXEROBJ)Mixer->hmx,
                                  &LineInfo,
                                  MIXER_GETLINEINFOF_SOURCE);
        if (Result == MMSYSERR_NOERROR)
        {
            LPMIXERCONTROL Controls = NULL;
            PSND_MIXER_CONNECTION Con;

            DPRINT("++ Source: %ws\n", LineInfo.szName);

            DispControls = 0;

            if (!SndMixerQueryControls(Mixer,
                                       &DispControls,
                                       &LineInfo,
                                       &Controls))
            {
                DPRINT("Failed to query connection controls\n");
                Ret = FALSE;
                break;
            }

            Con = (SND_MIXER_CONNECTION*) HeapAlloc(GetProcessHeap(),
                            HEAP_ZERO_MEMORY,
                            sizeof(SND_MIXER_CONNECTION));
            if (Con != NULL)
            {
                Con->Info = LineInfo;
                Con->Controls = Controls;
                Con->DisplayControls = DispControls;
                Con->Next = Line->Connections;
                Line->Connections = Con;
            }
            else
            {
                HeapFree(GetProcessHeap(),
                         0,
                         Controls);
            }
        }
        else
        {
            DPRINT("Failed to get connection information: %d\n", Result);
            Ret = FALSE;
            break;
        }
    }

    return Ret;
}