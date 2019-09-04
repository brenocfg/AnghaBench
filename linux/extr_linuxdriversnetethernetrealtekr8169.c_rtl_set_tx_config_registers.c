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
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 int InterFrameGap ; 
 scalar_t__ RTL_GIGA_MAC_VER_34 ; 
 scalar_t__ RTL_GIGA_MAC_VER_39 ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int TXCFG_AUTO_FIFO ; 
 int TX_DMA_BURST ; 
 int /*<<< orphan*/  TxConfig ; 
 int TxDMAShift ; 
 int TxInterFrameGapShift ; 

__attribute__((used)) static void rtl_set_tx_config_registers(struct rtl8169_private *tp)
{
	u32 val = TX_DMA_BURST << TxDMAShift |
		  InterFrameGap << TxInterFrameGapShift;

	if (tp->mac_version >= RTL_GIGA_MAC_VER_34 &&
	    tp->mac_version != RTL_GIGA_MAC_VER_39)
		val |= TXCFG_AUTO_FIFO;

	RTL_W32(tp, TxConfig, val);
}