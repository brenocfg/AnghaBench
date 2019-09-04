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
struct tape_request {int dummy; } ;
struct tape_device {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int __tape_cancel_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int
tape_cancel_io(struct tape_device *device, struct tape_request *request)
{
	int rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = __tape_cancel_io(device, request);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	return rc;
}