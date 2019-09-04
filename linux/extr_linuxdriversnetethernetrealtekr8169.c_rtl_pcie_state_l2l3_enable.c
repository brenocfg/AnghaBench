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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Config3 ; 
 int /*<<< orphan*/  RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rdy_to_L23 ; 

__attribute__((used)) static void rtl_pcie_state_l2l3_enable(struct rtl8169_private *tp, bool enable)
{
	u8 data;

	data = RTL_R8(tp, Config3);

	if (enable)
		data |= Rdy_to_L23;
	else
		data &= ~Rdy_to_L23;

	RTL_W8(tp, Config3, data);
}