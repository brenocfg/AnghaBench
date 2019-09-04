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
struct rfkill {int registered; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; int /*<<< orphan*/  sync_work; int /*<<< orphan*/  uevent_work; int /*<<< orphan*/  poll_work; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RFKILL_OP_DEL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_global_led_trigger_event () ; 
 int /*<<< orphan*/  rfkill_global_mutex ; 
 int /*<<< orphan*/  rfkill_led_trigger_unregister (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_send_events (struct rfkill*,int /*<<< orphan*/ ) ; 

void rfkill_unregister(struct rfkill *rfkill)
{
	BUG_ON(!rfkill);

	if (rfkill->ops->poll)
		cancel_delayed_work_sync(&rfkill->poll_work);

	cancel_work_sync(&rfkill->uevent_work);
	cancel_work_sync(&rfkill->sync_work);

	rfkill->registered = false;

	device_del(&rfkill->dev);

	mutex_lock(&rfkill_global_mutex);
	rfkill_send_events(rfkill, RFKILL_OP_DEL);
	list_del_init(&rfkill->node);
	rfkill_global_led_trigger_event();
	mutex_unlock(&rfkill_global_mutex);

	rfkill_led_trigger_unregister(rfkill);
}