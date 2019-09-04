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
struct mt76x2_dev {int rxfilter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2u_mac_reset_counters (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_wpdma (struct mt76x2_dev*) ; 

int mt76x2u_mac_start(struct mt76x2_dev *dev)
{
	mt76x2u_mac_reset_counters(dev);

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
	wait_for_wpdma(dev);
	usleep_range(50, 100);

	mt76_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);

	return 0;
}