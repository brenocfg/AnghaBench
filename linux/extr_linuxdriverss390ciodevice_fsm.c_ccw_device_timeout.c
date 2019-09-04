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
struct timer_list {int dummy; } ;
struct ccw_device_private {struct ccw_device* cdev; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  ccw_timeout_log (struct ccw_device*) ; 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct ccw_device_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ccw_device_private* priv ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ timeout_log_enabled ; 
 int /*<<< orphan*/  timer ; 

void
ccw_device_timeout(struct timer_list *t)
{
	struct ccw_device_private *priv = from_timer(priv, t, timer);
	struct ccw_device *cdev = priv->cdev;

	spin_lock_irq(cdev->ccwlock);
	if (timeout_log_enabled)
		ccw_timeout_log(cdev);
	dev_fsm_event(cdev, DEV_EVENT_TIMEOUT);
	spin_unlock_irq(cdev->ccwlock);
}