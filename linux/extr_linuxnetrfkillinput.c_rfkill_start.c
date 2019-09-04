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
struct input_handle {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  sw; int /*<<< orphan*/  swbit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  SW_RFKILL_ALL ; 
 int /*<<< orphan*/  rfkill_schedule_evsw_rfkillall (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfkill_start(struct input_handle *handle)
{
	/*
	 * Take event_lock to guard against configuration changes, we
	 * should be able to deal with concurrency with rfkill_event()
	 * just fine (which event_lock will also avoid).
	 */
	spin_lock_irq(&handle->dev->event_lock);

	if (test_bit(EV_SW, handle->dev->evbit) &&
	    test_bit(SW_RFKILL_ALL, handle->dev->swbit))
		rfkill_schedule_evsw_rfkillall(test_bit(SW_RFKILL_ALL,
							handle->dev->sw));

	spin_unlock_irq(&handle->dev->event_lock);
}