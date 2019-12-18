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
typedef  short** xtalk_coefs_t ;
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,short) ; 

__attribute__((used)) static void
vortex_XtalkHw_SetRightEQ(vortex_t * vortex, short arg_0, short arg_4,
			  xtalk_coefs_t const coefs)
{
	int i;

	for (i = 0; i < 5; i++) {
		hwwrite(vortex->mmio, 0x242b4 + i * 0x24, coefs[i][0]);
		hwwrite(vortex->mmio, 0x242b8 + i * 0x24, coefs[i][1]);
		hwwrite(vortex->mmio, 0x242bc + i * 0x24, coefs[i][2]);
		hwwrite(vortex->mmio, 0x242c0 + i * 0x24, coefs[i][3]);
		hwwrite(vortex->mmio, 0x242c4 + i * 0x24, coefs[i][4]);
	}
	hwwrite(vortex->mmio, 0x24540, arg_0 & 0xffff);
	hwwrite(vortex->mmio, 0x24544, arg_4 & 0xffff);
}