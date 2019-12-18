#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* mixwt; int /*<<< orphan*/  mmio; int /*<<< orphan*/ * mixplayb; int /*<<< orphan*/  fixed_res; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_MIXIN (int) ; 
 int /*<<< orphan*/  ADB_WTOUT (int,int) ; 
 int NR_WT ; 
 int NR_WTBLOCKS ; 
 int NR_WTROUTES ; 
 scalar_t__ VORTEX_IS_QUAD (TYPE_1__*) ; 
 int /*<<< orphan*/  VORTEX_RESOURCE_MIXIN ; 
 int /*<<< orphan*/  WT_RUN (int) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vortex_adb_checkinout (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_connection_mixin_mix (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_route (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_wt_connect(vortex_t * vortex, int en)
{
	int i, ii, mix;

#define NR_WTROUTES 6
#ifdef CHIP_AU8830
#define NR_WTBLOCKS 2
#else
#define NR_WTBLOCKS 1
#endif

	for (i = 0; i < NR_WTBLOCKS; i++) {
		for (ii = 0; ii < NR_WTROUTES; ii++) {
			mix =
			    vortex_adb_checkinout(vortex,
						  vortex->fixed_res, en,
						  VORTEX_RESOURCE_MIXIN);
			vortex->mixwt[(i * NR_WTROUTES) + ii] = mix;

			vortex_route(vortex, en, 0x11,
				     ADB_WTOUT(i, ii + 0x20), ADB_MIXIN(mix));

			vortex_connection_mixin_mix(vortex, en, mix,
						    vortex->mixplayb[ii % 2], 0);
			if (VORTEX_IS_QUAD(vortex))
				vortex_connection_mixin_mix(vortex, en,
							    mix,
							    vortex->mixplayb[2 +
								     (ii % 2)], 0);
		}
	}
	for (i = 0; i < NR_WT; i++) {
		hwwrite(vortex->mmio, WT_RUN(i), 1);
	}
}