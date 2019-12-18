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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int MIXER_RTBASE_SIZE ; 
 int NR_MIXOUT ; 
 scalar_t__ VORTEX_MIXER_RTBASE ; 
 scalar_t__ VORTEX_MIXER_SR ; 
 scalar_t__ VORTEX_MIX_ENIN ; 
 scalar_t__ VORTEX_MIX_INVOL_A ; 
 scalar_t__ VORTEX_MIX_INVOL_B ; 
 scalar_t__ VORTEX_MIX_SMP ; 
 scalar_t__ VORTEX_MIX_VOL_A ; 
 scalar_t__ VORTEX_MIX_VOL_B ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mchannels ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rampchs ; 

__attribute__((used)) static void vortex_mixer_init(vortex_t * vortex)
{
	u32 addr;
	int x;

	// FIXME: get rid of this crap.
	memset(mchannels, 0, NR_MIXOUT * sizeof(int));
	memset(rampchs, 0, NR_MIXOUT * sizeof(int));

	addr = VORTEX_MIX_SMP + 0x17c;
	for (x = 0x5f; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0);
		addr -= 4;
	}
	addr = VORTEX_MIX_ENIN + 0x1fc;
	for (x = 0x7f; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0);
		addr -= 4;
	}
	addr = VORTEX_MIX_SMP + 0x17c;
	for (x = 0x5f; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0);
		addr -= 4;
	}
	addr = VORTEX_MIX_INVOL_A + 0x7fc;
	for (x = 0x1ff; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0x80);
		addr -= 4;
	}
	addr = VORTEX_MIX_VOL_A + 0x3c;
	for (x = 0xf; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0x80);
		addr -= 4;
	}
	addr = VORTEX_MIX_INVOL_B + 0x7fc;
	for (x = 0x1ff; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0x80);
		addr -= 4;
	}
	addr = VORTEX_MIX_VOL_B + 0x3c;
	for (x = 0xf; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0x80);
		addr -= 4;
	}
	addr = VORTEX_MIXER_RTBASE + (MIXER_RTBASE_SIZE - 1) * 4;
	for (x = (MIXER_RTBASE_SIZE - 1); x >= 0; x--) {
		hwwrite(vortex->mmio, addr, 0x0);
		addr -= 4;
	}
	hwwrite(vortex->mmio, VORTEX_MIXER_SR, 0);

	/* Set clipping ceiling (this may be all wrong). */
	/*
	for (x = 0; x < 0x80; x++) {
		hwwrite(vortex->mmio, VORTEX_MIXER_CLIP + (x << 2), 0x3ffff);
	}
	*/
	/*
	   call CAsp4Mix__Initialize_CAsp4HwIO____CAsp4Mixer____
	   Register ISR callback for volume smooth fade out.
	   Maybe this avoids clicks when press "stop" ?
	 */
}