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
struct dasd_device {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 struct dasd_device* dasd_device_from_cdev_locked (struct ccw_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

struct dasd_device *
dasd_device_from_cdev(struct ccw_device *cdev)
{
	struct dasd_device *device;
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	device = dasd_device_from_cdev_locked(cdev);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	return device;
}