#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fdwControl; int dwControlType; } ;
struct TYPE_5__ {scalar_t__ hmx; } ;
typedef  TYPE_1__* PSND_MIXER ;
typedef  TYPE_2__* LPMIXERCONTROL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MIXERCONTROL_CONTROLF_DISABLED ; 
#define  MIXERCONTROL_CT_CLASS_FADER 129 
 int MIXERCONTROL_CT_CLASS_MASK ; 
#define  MIXERCONTROL_CT_CLASS_SWITCH 128 
 int /*<<< orphan*/  TRUE ; 

BOOL
SndMixerIsDisplayControl(PSND_MIXER Mixer,
                         LPMIXERCONTROL Control)
{
    if (Mixer->hmx && !(Control->fdwControl & MIXERCONTROL_CONTROLF_DISABLED))
    {
        switch (Control->dwControlType & MIXERCONTROL_CT_CLASS_MASK)
        {
            case MIXERCONTROL_CT_CLASS_FADER:
            case MIXERCONTROL_CT_CLASS_SWITCH:
                return TRUE;
        }
    }

    return FALSE;
}