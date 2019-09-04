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
struct TYPE_2__ {int /*<<< orphan*/  stat_work; } ;
struct mt76_dev {int /*<<< orphan*/  state; TYPE_1__ usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_READING_STATS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt76u_stop_stat_wk(struct mt76_dev *dev)
{
	cancel_delayed_work_sync(&dev->usb.stat_work);
	clear_bit(MT76_READING_STATS, &dev->state);
}