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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SYSC_REG_RSTCTRL ; 
 int /*<<< orphan*/  rt_sysc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_sysc_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void fe_reset(u32 reset_bits)
{
	u32 t;

	t = rt_sysc_r32(SYSC_REG_RSTCTRL);
	t |= reset_bits;
	rt_sysc_w32(t, SYSC_REG_RSTCTRL);
	usleep_range(10, 20);

	t &= ~reset_bits;
	rt_sysc_w32(t, SYSC_REG_RSTCTRL);
	usleep_range(10, 20);
}