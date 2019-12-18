#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int* rampchs ; 
 int /*<<< orphan*/  vortex_mix_killinput (int /*<<< orphan*/ *,unsigned char,int) ; 

__attribute__((used)) static void
vortex_mix_disableinput(vortex_t * vortex, unsigned char mix, int channel,
			int ramp)
{
	if (ramp) {
		rampchs[mix] |= (1 << channel);
		// Register callback.
		//vortex_mix_startrampvolume(vortex);
		vortex_mix_killinput(vortex, mix, channel);
	} else
		vortex_mix_killinput(vortex, mix, channel);
}