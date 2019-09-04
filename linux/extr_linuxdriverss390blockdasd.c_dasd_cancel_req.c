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
struct dasd_device {int /*<<< orphan*/  cdev; } ;
struct dasd_ccw_req {struct dasd_device* startdev; } ;

/* Variables and functions */
 int __dasd_cancel_req (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int dasd_cancel_req(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device = cqr->startdev;
	unsigned long flags;
	int rc;

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	rc = __dasd_cancel_req(cqr);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	return rc;
}