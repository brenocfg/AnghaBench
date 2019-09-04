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
struct mt76x2_dev {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  cal_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_mcu_set_radio_state (struct mt76x2_dev*,int) ; 

void mt76x2_stop_hardware(struct mt76x2_dev *dev)
{
	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mac_work);
	mt76x2_mcu_set_radio_state(dev, false);
	mt76x2_mac_stop(dev, false);
}