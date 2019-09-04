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
 int /*<<< orphan*/  ADB_CODECOUT (int) ; 
 int /*<<< orphan*/  ADB_EQIN (int) ; 
 int /*<<< orphan*/  ADB_EQOUT (int) ; 
 scalar_t__ VORTEX_IS_QUAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_connection_mix_adb (int /*<<< orphan*/ *,int,int,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_mix_setvolumebyte (int /*<<< orphan*/ *,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_route (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_connect_codecplay(vortex_t * vortex, int en, unsigned char mixers[])
{
#ifdef CHIP_AU8820
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_CODECOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_CODECOUT(1));
#else
#if 1
	// Connect front channels through EQ.
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_EQIN(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_EQIN(1));
	/* Lower volume, since EQ has some gain. */
	vortex_mix_setvolumebyte(vortex, mixers[0], 0);
	vortex_mix_setvolumebyte(vortex, mixers[1], 0);
	vortex_route(vortex, en, 0x11, ADB_EQOUT(0), ADB_CODECOUT(0));
	vortex_route(vortex, en, 0x11, ADB_EQOUT(1), ADB_CODECOUT(1));

	/* Check if reg 0x28 has SDAC bit set. */
	if (VORTEX_IS_QUAD(vortex)) {
		/* Rear channel. Note: ADB_CODECOUT(0+2) and (1+2) is for AC97 modem */
		vortex_connection_mix_adb(vortex, en, 0x11, mixers[2],
					  ADB_CODECOUT(0 + 4));
		vortex_connection_mix_adb(vortex, en, 0x11, mixers[3],
					  ADB_CODECOUT(1 + 4));
		/* pr_debug( "SDAC detected "); */
	}
#else
	// Use plain direct output to codec.
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_CODECOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_CODECOUT(1));
#endif
#endif
}