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
typedef  int u16 ;
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT431_REG_CXLO ; 
 int /*<<< orphan*/  bt431_select_reg (struct bt431_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt431_write_reg_inc (struct bt431_regs*,int) ; 

__attribute__((used)) static inline void bt431_position_cursor(struct bt431_regs *regs, u16 x, u16 y)
{
	/*
	 * Magic from the MACH sources.
	 *
	 * Cx = x + D + H - P
	 *  P = 37 if 1:1, 52 if 4:1, 57 if 5:1
	 *  D = pixel skew between outdata and external data
	 *  H = pixels between HSYNCH falling and active video
	 *
	 * Cy = y + V - 32
	 *  V = scanlines between HSYNCH falling, two or more
	 *      clocks after VSYNCH falling, and active video
	 */
	x += 412 - 52;
	y += 68 - 32;

	/* Use autoincrement. */
	bt431_select_reg(regs, BT431_REG_CXLO);
	bt431_write_reg_inc(regs, x & 0xff); /* BT431_REG_CXLO */
	bt431_write_reg_inc(regs, (x >> 8) & 0x0f); /* BT431_REG_CXHI */
	bt431_write_reg_inc(regs, y & 0xff); /* BT431_REG_CYLO */
	bt431_write_reg_inc(regs, (y >> 8) & 0x0f); /* BT431_REG_CYHI */
}