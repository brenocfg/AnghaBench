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
typedef  int* xtalk_dline_t ;
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
vortex_XtalkHw_SetLeftDline(vortex_t * vortex, xtalk_dline_t const dline)
{
	int i;

	for (i = 0; i < 0x20; i++) {
		hwwrite(vortex->mmio, 0x24000 + (i << 2), dline[i] & 0xffff);
		hwwrite(vortex->mmio, 0x24080 + (i << 2), dline[i] >> 0x10);
	}
}