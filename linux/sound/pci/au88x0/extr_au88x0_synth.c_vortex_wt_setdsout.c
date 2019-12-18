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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  WT_DSREG (int) ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vortex_wt_setdsout(vortex_t * vortex, u32 wt, int en)
{
	int temp;

	/* There is one DSREG register for each bank (32 voices each). */
	temp = hwread(vortex->mmio, WT_DSREG((wt >= 0x20) ? 1 : 0));
	if (en)
		temp |= (1 << (wt & 0x1f));
	else
		temp &= ~(1 << (wt & 0x1f));
	hwwrite(vortex->mmio, WT_DSREG((wt >= 0x20) ? 1 : 0), temp);
}