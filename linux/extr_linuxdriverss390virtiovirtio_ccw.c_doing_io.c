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
struct virtio_ccw_device {int curr_io; int /*<<< orphan*/  cdev; scalar_t__ err; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int doing_io(struct virtio_ccw_device *vcdev, __u32 flag)
{
	unsigned long flags;
	__u32 ret;

	spin_lock_irqsave(get_ccwdev_lock(vcdev->cdev), flags);
	if (vcdev->err)
		ret = 0;
	else
		ret = vcdev->curr_io & flag;
	spin_unlock_irqrestore(get_ccwdev_lock(vcdev->cdev), flags);
	return ret;
}