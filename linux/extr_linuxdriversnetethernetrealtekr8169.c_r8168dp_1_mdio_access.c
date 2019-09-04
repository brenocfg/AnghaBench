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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPHY_RXER_NUM ; 
 int /*<<< orphan*/  OCPAR ; 
 int OCPAR_GPHY_WRITE_CMD ; 
 int /*<<< orphan*/  OCPDR ; 
 int OCPDR_GPHY_REG_SHIFT ; 
 int OCPDR_REG_MASK ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_ocpar_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void r8168dp_1_mdio_access(struct rtl8169_private *tp, int reg, u32 data)
{
	RTL_W32(tp, OCPDR, data | ((reg & OCPDR_REG_MASK) << OCPDR_GPHY_REG_SHIFT));
	RTL_W32(tp, OCPAR, OCPAR_GPHY_WRITE_CMD);
	RTL_W32(tp, EPHY_RXER_NUM, 0);

	rtl_udelay_loop_wait_low(tp, &rtl_ocpar_cond, 1000, 100);
}