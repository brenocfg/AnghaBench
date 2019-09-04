#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  MixerId; int /*<<< orphan*/ * hmx; } ;
typedef  TYPE_1__* PSND_MIXER ;

/* Variables and functions */
 int /*<<< orphan*/  NO_MIXER_SELECTED ; 
 int /*<<< orphan*/  mixerClose (int /*<<< orphan*/ *) ; 

VOID
SndMixerClose(PSND_MIXER Mixer)
{
    if (Mixer->hmx != NULL)
    {
      mixerClose(Mixer->hmx);
      Mixer->hmx = NULL;
      Mixer->MixerId = NO_MIXER_SELECTED;
    }
}