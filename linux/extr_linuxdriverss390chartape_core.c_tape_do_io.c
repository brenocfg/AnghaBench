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
struct tape_device {int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int __tape_start_request (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/ * __tape_wake_up ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tape_do_io(struct tape_device *device, struct tape_request *request)
{
	int rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	/* Setup callback */
	request->callback = __tape_wake_up;
	request->callback_data = &device->wait_queue;
	/* Add request to request queue and try to start it. */
	rc = __tape_start_request(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	if (rc)
		return rc;
	/* Request added to the queue. Wait for its completion. */
	wait_event(device->wait_queue, (request->callback == NULL));
	/* Get rc from request */
	return request->rc;
}