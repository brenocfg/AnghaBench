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
struct rtl8169_private {int /*<<< orphan*/  ocp_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChipCmd ; 
 int CmdRxEnb ; 
 int CmdTxEnb ; 
 int /*<<< orphan*/  MCU ; 
 int /*<<< orphan*/  MISC ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  OCP_STD_PHY_BASE ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int RXDV_GATED_EN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int r8168_mac_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_link_list_ready_cond ; 
 int /*<<< orphan*/  rtl_rxtx_empty_cond ; 
 int /*<<< orphan*/  rtl_txcfg_empty_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_high (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void rtl_hw_init_8168g(struct rtl8169_private *tp)
{
	u32 data;

	tp->ocp_base = OCP_STD_PHY_BASE;

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | RXDV_GATED_EN);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_txcfg_empty_cond, 100, 42))
		return;

	if (!rtl_udelay_loop_wait_high(tp, &rtl_rxtx_empty_cond, 100, 42))
		return;

	RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) & ~(CmdTxEnb | CmdRxEnb));
	msleep(1);
	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	data = r8168_mac_ocp_read(tp, 0xe8de);
	data &= ~(1 << 14);
	r8168_mac_ocp_write(tp, 0xe8de, data);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_link_list_ready_cond, 100, 42))
		return;

	data = r8168_mac_ocp_read(tp, 0xe8de);
	data |= (1 << 15);
	r8168_mac_ocp_write(tp, 0xe8de, data);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_link_list_ready_cond, 100, 42))
		return;
}