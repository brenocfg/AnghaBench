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
struct mt76x2_dev {int /*<<< orphan*/  cal_work; int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76u_stop_stat_wk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2u_mac_stop (struct mt76x2_dev*) ; 

void mt76x2u_stop_hw(struct mt76x2_dev *dev)
{
	mt76u_stop_stat_wk(&dev->mt76);
	cancel_delayed_work_sync(&dev->cal_work);
	mt76x2u_mac_stop(dev);
}