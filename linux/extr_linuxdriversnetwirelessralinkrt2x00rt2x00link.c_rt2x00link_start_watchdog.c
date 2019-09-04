#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct link {int /*<<< orphan*/  watchdog_work; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; TYPE_2__* ops; int /*<<< orphan*/  flags; struct link link; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {scalar_t__ watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  WATCHDOG_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00link_start_watchdog(struct rt2x00_dev *rt2x00dev)
{
	struct link *link = &rt2x00dev->link;

	if (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    rt2x00dev->ops->lib->watchdog)
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->watchdog_work,
					     WATCHDOG_INTERVAL);
}