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
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT_CMB_CTRL ; 
 int /*<<< orphan*/  MT_COEXCFG0 ; 
 int /*<<< orphan*/  MT_COEXCFG3 ; 
 int /*<<< orphan*/  MT_WLAN_FUN_CTRL ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x0_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mt76x0_ant_select(struct mt76x0_dev *dev)
{
	/* Single antenna mode. */
	mt76_rmw(dev, MT_WLAN_FUN_CTRL, BIT(5), BIT(6));
	mt76_clear(dev, MT_CMB_CTRL, BIT(14) | BIT(12));
	mt76_clear(dev, MT_COEXCFG0, BIT(2));
	mt76_rmw(dev, MT_COEXCFG3, BIT(5) | BIT(4) | BIT(3) | BIT(2), BIT(1));
}