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
struct tape_request {int rc; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * callback_data; } ;
struct tape_device {int /*<<< orphan*/  cdev_id; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int ERESTARTSYS ; 
 int __tape_cancel_io (struct tape_device*,struct tape_request*) ; 
 int __tape_start_request (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/ * __tape_wake_up_interruptible ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tape_do_io_interruptible(struct tape_device *device,
			 struct tape_request *request)
{
	int rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Setup callback */
	request->callback = __tape_wake_up_interruptible;
	request->callback_data = &device->wait_queue;
	rc = __tape_start_request(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	if (rc)
		return rc;
	/* Request added to the queue. Wait for its completion. */
	rc = wait_event_interruptible(device->wait_queue,
				      (request->callback == NULL));
	if (rc != -ERESTARTSYS)
		/* Request finished normally. */
		return request->rc;

	/* Interrupted by a signal. We have to stop the current request. */
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = __tape_cancel_io(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	if (rc == 0) {
		/* Wait for the interrupt that acknowledges the halt. */
		do {
			rc = wait_event_interruptible(
				device->wait_queue,
				(request->callback == NULL)
			);
		} while (rc == -ERESTARTSYS);

		DBF_EVENT(3, "IO stopped on %08x\n", device->cdev_id);
		rc = -ERESTARTSYS;
	}
	return rc;
}