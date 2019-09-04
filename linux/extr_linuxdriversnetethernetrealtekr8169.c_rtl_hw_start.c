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
struct rtl8169_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* hw_start ) (struct rtl8169_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int Cfg9346_Lock ; 
 int Cfg9346_Unlock ; 
 int /*<<< orphan*/  ChipCmd ; 
 int CmdRxEnb ; 
 int CmdTxEnb ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  MultiIntr ; 
 int RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_init_rxcfg (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_irq_enable_all (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_rx_max_size (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_rx_tx_desc_registers (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_tx_config_registers (struct rtl8169_private*) ; 
 int /*<<< orphan*/  stub1 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start(struct  rtl8169_private *tp)
{
	RTL_W8(tp, Cfg9346, Cfg9346_Unlock);

	tp->hw_start(tp);

	rtl_set_rx_max_size(tp);
	rtl_set_rx_tx_desc_registers(tp);
	RTL_W8(tp, Cfg9346, Cfg9346_Lock);

	/* Initially a 10 us delay. Turned it into a PCI commit. - FR */
	RTL_R8(tp, IntrMask);
	RTL_W8(tp, ChipCmd, CmdTxEnb | CmdRxEnb);
	rtl_init_rxcfg(tp);
	rtl_set_tx_config_registers(tp);

	rtl_set_rx_mode(tp->dev);
	/* no early-rx interrupts */
	RTL_W16(tp, MultiIntr, RTL_R16(tp, MultiIntr) & 0xf000);
	rtl_irq_enable_all(tp);
}