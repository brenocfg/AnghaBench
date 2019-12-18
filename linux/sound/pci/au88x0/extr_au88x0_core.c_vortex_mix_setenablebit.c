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
 scalar_t__ VORTEX_MIX_ENIN ; 
 scalar_t__ VORTEX_MIX_INVOL_B ; 
 scalar_t__ VORTEX_MIX_SMP ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
vortex_mix_setenablebit(vortex_t * vortex, unsigned char mix, int mixin, int en)
{
	int temp, addr;

	if (mixin < 0)
		addr = (mixin + 3);
	else
		addr = mixin;
	addr = ((mix << 3) + (addr >> 2)) << 2;
	temp = hwread(vortex->mmio, VORTEX_MIX_ENIN + addr);
	if (en)
		temp |= (1 << (mixin & 3));
	else
		temp &= ~(1 << (mixin & 3));
	/* Mute input. Astatic void crackling? */
	hwwrite(vortex->mmio,
		VORTEX_MIX_INVOL_B + (((mix << 5) + mixin) << 2), 0x80);
	/* Looks like clear buffer. */
	hwwrite(vortex->mmio, VORTEX_MIX_SMP + (mixin << 2), 0x0);
	hwwrite(vortex->mmio, VORTEX_MIX_SMP + 4 + (mixin << 2), 0x0);
	/* Write enable bit. */
	hwwrite(vortex->mmio, VORTEX_MIX_ENIN + addr, temp);
}