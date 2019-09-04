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
typedef  int u32 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int RXDMA_USB_AGG_ENABLE ; 
 int /*<<< orphan*/  TRXDMA_CTRL_RXDMA_AGG_EN ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8723bu_init_aggregation(struct rtl8xxxu_priv *priv)
{
	u32 agg_rx;
	u8 agg_ctrl;

	/*
	 * For now simply disable RX aggregation
	 */
	agg_ctrl = rtl8xxxu_read8(priv, REG_TRXDMA_CTRL);
	agg_ctrl &= ~TRXDMA_CTRL_RXDMA_AGG_EN;

	agg_rx = rtl8xxxu_read32(priv, REG_RXDMA_AGG_PG_TH);
	agg_rx &= ~RXDMA_USB_AGG_ENABLE;
	agg_rx &= ~0xff0f;

	rtl8xxxu_write8(priv, REG_TRXDMA_CTRL, agg_ctrl);
	rtl8xxxu_write32(priv, REG_RXDMA_AGG_PG_TH, agg_rx);
}