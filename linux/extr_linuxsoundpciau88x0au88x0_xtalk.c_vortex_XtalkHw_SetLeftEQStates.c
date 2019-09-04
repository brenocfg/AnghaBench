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
typedef  int /*<<< orphan*/ ** xtalk_state_t ;
typedef  int /*<<< orphan*/ * xtalk_instate_t ;
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_XtalkHw_SetLeftEQStates(vortex_t * vortex,
			       xtalk_instate_t const arg_0,
			       xtalk_state_t const coefs)
{
	int i;

	for (i = 0; i < 5; i++) {
		hwwrite(vortex->mmio, 0x24214 + i * 0x24, coefs[i][0]);
		hwwrite(vortex->mmio, 0x24218 + i * 0x24, coefs[i][1]);
		hwwrite(vortex->mmio, 0x2421C + i * 0x24, coefs[i][2]);
		hwwrite(vortex->mmio, 0x24220 + i * 0x24, coefs[i][3]);
	}
	hwwrite(vortex->mmio, 0x244F8, arg_0[0]);
	hwwrite(vortex->mmio, 0x244FC, arg_0[1]);
	hwwrite(vortex->mmio, 0x24500, arg_0[2]);
	hwwrite(vortex->mmio, 0x24504, arg_0[3]);
}