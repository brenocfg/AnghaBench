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
struct gb_interface {int mode_switch; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode_switch_work; int /*<<< orphan*/  mode_switch_completion; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

int gb_interface_request_mode_switch(struct gb_interface *intf)
{
	int ret = 0;

	mutex_lock(&intf->mutex);
	if (intf->mode_switch) {
		ret = -EBUSY;
		goto out_unlock;
	}

	intf->mode_switch = true;
	reinit_completion(&intf->mode_switch_completion);

	/*
	 * Get a reference to the interface device, which will be put once the
	 * mode switch is complete.
	 */
	get_device(&intf->dev);

	if (!queue_work(system_long_wq, &intf->mode_switch_work)) {
		put_device(&intf->dev);
		ret = -EBUSY;
		goto out_unlock;
	}

out_unlock:
	mutex_unlock(&intf->mutex);

	return ret;
}