#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {scalar_t__ MixersCount; int /*<<< orphan*/  MixerId; int /*<<< orphan*/  hWndNotification; } ;
typedef  int /*<<< orphan*/  SND_MIXER ;
typedef  TYPE_1__* PSND_MIXER ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NO_MIXER_SELECTED ; 
 int /*<<< orphan*/  SndMixerSelect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mixerGetNumDevs () ; 

PSND_MIXER
SndMixerCreate(HWND hWndNotification, UINT MixerId)
{
    PSND_MIXER Mixer = (PSND_MIXER) HeapAlloc(GetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 sizeof(SND_MIXER));
    if (Mixer != NULL)
    {
        Mixer->hWndNotification = hWndNotification;
        Mixer->MixersCount = mixerGetNumDevs();
        Mixer->MixerId = NO_MIXER_SELECTED;

        if (Mixer->MixersCount > 0)
        {
            /* select the first mixer by default */
            SndMixerSelect(Mixer, MixerId);
        }
    }

    return Mixer;
}