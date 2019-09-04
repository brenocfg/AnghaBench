#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cDestinations; } ;
struct TYPE_5__ {TYPE_1__ Caps; scalar_t__ hmx; } ;
typedef  TYPE_2__* PSND_MIXER ;
typedef  int INT ;

/* Variables and functions */

INT
SndMixerGetDestinationCount(PSND_MIXER Mixer)
{
    return (Mixer->hmx ? (INT)Mixer->Caps.cDestinations : -1);
}