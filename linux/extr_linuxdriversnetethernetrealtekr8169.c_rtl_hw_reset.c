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
 int /*<<< orphan*/  ChipCmd ; 
 int /*<<< orphan*/  CmdReset ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_chipcmd_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void rtl_hw_reset(struct rtl8169_private *tp)
{
	RTL_W8(tp, ChipCmd, CmdReset);

	rtl_udelay_loop_wait_low(tp, &rtl_chipcmd_cond, 100, 100);
}