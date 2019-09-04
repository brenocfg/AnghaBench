#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ofdm; } ;
struct mt76x2_dev {TYPE_1__ rate_power; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG ; 
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG_AUTO_PADJ ; 
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG_PROT_PADJ ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_tx_get_txpwr_adj (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76x2_tx_set_txpwr_auto(struct mt76x2_dev *dev, s8 txpwr)
{
	s8 txpwr_adj;

	txpwr_adj = mt76x2_tx_get_txpwr_adj(dev, txpwr,
					    dev->rate_power.ofdm[4]);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_PROT_PADJ, txpwr_adj);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_AUTO_PADJ, txpwr_adj);
}