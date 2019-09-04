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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPHYAR ; 
 int EPHYAR_DATA_MASK ; 
 int EPHYAR_REG_MASK ; 
 int EPHYAR_REG_SHIFT ; 
 int EPHYAR_WRITE_CMD ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_ephyar_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl_ephy_write(struct rtl8169_private *tp, int reg_addr, int value)
{
	RTL_W32(tp, EPHYAR, EPHYAR_WRITE_CMD | (value & EPHYAR_DATA_MASK) |
		(reg_addr & EPHYAR_REG_MASK) << EPHYAR_REG_SHIFT);

	rtl_udelay_loop_wait_low(tp, &rtl_ephyar_cond, 10, 100);

	udelay(10);
}