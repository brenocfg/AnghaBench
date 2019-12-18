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
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 scalar_t__ VORTEX_MIX_VOL_A ; 
 scalar_t__ VORTEX_MIX_VOL_B ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,unsigned char) ; 

__attribute__((used)) static void
vortex_mix_setvolumebyte(vortex_t * vortex, unsigned char mix,
			 unsigned char vol)
{
	int temp;
	hwwrite(vortex->mmio, VORTEX_MIX_VOL_A + (mix << 2), vol);
	if (1) {		/*if (this_10) */
		temp = hwread(vortex->mmio, VORTEX_MIX_VOL_B + (mix << 2));
		if ((temp != 0x80) || (vol == 0x80))
			return;
	}
	hwwrite(vortex->mmio, VORTEX_MIX_VOL_B + (mix << 2), vol);
}