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
struct urdev {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct urdev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  urdev_get (struct urdev*) ; 

__attribute__((used)) static struct urdev *urdev_get_from_cdev(struct ccw_device *cdev)
{
	struct urdev *urd;
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	urd = dev_get_drvdata(&cdev->dev);
	if (urd)
		urdev_get(urd);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	return urd;
}