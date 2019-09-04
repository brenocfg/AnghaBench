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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SOSSI_INIT3_REG ; 
 int sossi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sossi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _set_bits_per_cycle(int bus_pick_count, int bus_pick_width)
{
	u32 l;

	l = sossi_read_reg(SOSSI_INIT3_REG);
	l &= ~0x3ff;
	l |= ((bus_pick_count - 1) << 5) | ((bus_pick_width - 1) & 0x1f);
	sossi_write_reg(SOSSI_INIT3_REG, l);
}