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
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_ET ; 
 int /*<<< orphan*/  mt76_set (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x2u_mac_resume(struct mt76x2_dev *dev)
{
	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);
	mt76_set(dev, MT_TXOP_CTRL_CFG, BIT(20));
	mt76_set(dev, MT_TXOP_HLDR_ET, BIT(1));
}