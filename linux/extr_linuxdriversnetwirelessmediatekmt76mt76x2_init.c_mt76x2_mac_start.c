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
struct mt76x2_dev {int rxfilter; int /*<<< orphan*/  aggr_stats; } ;

/* Variables and functions */
 int MT_INT_RX_DONE_ALL ; 
 int MT_INT_TX_DONE_ALL ; 
 int MT_INT_TX_STAT ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  MT_TX_AGG_CNT (int) ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_irq_enable (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_wpdma (struct mt76x2_dev*) ; 

int mt76x2_mac_start(struct mt76x2_dev *dev)
{
	int i;

	for (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_AGG_CNT(i));

	for (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_STAT_FIFO);

	memset(dev->aggr_stats, 0, sizeof(dev->aggr_stats));

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
	wait_for_wpdma(dev);
	usleep_range(50, 100);

	mt76_set(dev, MT_WPDMA_GLO_CFG,
		 MT_WPDMA_GLO_CFG_TX_DMA_EN |
		 MT_WPDMA_GLO_CFG_RX_DMA_EN);

	mt76_clear(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	mt76_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);

	mt76x2_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL |
			       MT_INT_TX_STAT);

	return 0;
}