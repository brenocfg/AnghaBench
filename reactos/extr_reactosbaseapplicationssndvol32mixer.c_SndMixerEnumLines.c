#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* Lines; scalar_t__ hmx; } ;
struct TYPE_6__ {int /*<<< orphan*/  DisplayControls; int /*<<< orphan*/  Info; struct TYPE_6__* Next; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSND_MIXER_DESTINATION ;
typedef  TYPE_2__* PSND_MIXER ;
typedef  int /*<<< orphan*/  (* PFNSNDMIXENUMLINES ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
SndMixerEnumLines(PSND_MIXER Mixer,
                  PFNSNDMIXENUMLINES EnumProc,
                  PVOID Context)
{
    if (Mixer->hmx)
    {
        PSND_MIXER_DESTINATION Line;

        for (Line = Mixer->Lines; Line != NULL; Line = Line->Next)
        {
            if (!EnumProc(Mixer,
                          &Line->Info,
                          Line->DisplayControls,
                          Context))
            {
                return FALSE;
            }
        }

        return TRUE;
    }

    return FALSE;
}