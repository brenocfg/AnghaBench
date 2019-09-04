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
struct mt76x0_dev {int /*<<< orphan*/  stat_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_mac_stop_hw (struct mt76x0_dev*) ; 

void mt76x0_mac_stop(struct mt76x0_dev *dev)
{
	mt76x0_mac_stop_hw(dev);
	flush_delayed_work(&dev->stat_work);
	cancel_delayed_work_sync(&dev->stat_work);
}