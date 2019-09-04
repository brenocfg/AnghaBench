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
struct usb_device {int dummy; } ;
struct usb_dev_state {int /*<<< orphan*/  wait; struct usb_device* dev; } ;
struct async {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct async* async_getcompleted (struct usb_dev_state*) ; 
 int /*<<< orphan*/  connected (struct usb_dev_state*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct async *reap_as(struct usb_dev_state *ps)
{
	DECLARE_WAITQUEUE(wait, current);
	struct async *as = NULL;
	struct usb_device *dev = ps->dev;

	add_wait_queue(&ps->wait, &wait);
	for (;;) {
		__set_current_state(TASK_INTERRUPTIBLE);
		as = async_getcompleted(ps);
		if (as || !connected(ps))
			break;
		if (signal_pending(current))
			break;
		usb_unlock_device(dev);
		schedule();
		usb_lock_device(dev);
	}
	remove_wait_queue(&ps->wait, &wait);
	set_current_state(TASK_RUNNING);
	return as;
}