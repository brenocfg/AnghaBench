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
struct virtio_ccw_device {int /*<<< orphan*/  vdev; scalar_t__ device_lost; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unregister_virtio_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_break_device (int /*<<< orphan*/ *) ; 
 struct virtio_ccw_device* virtio_grab_drvdata (struct ccw_device*) ; 

__attribute__((used)) static int virtio_ccw_offline(struct ccw_device *cdev)
{
	unsigned long flags;
	struct virtio_ccw_device *vcdev = virtio_grab_drvdata(cdev);

	if (!vcdev)
		return 0;
	if (vcdev->device_lost)
		virtio_break_device(&vcdev->vdev);
	unregister_virtio_device(&vcdev->vdev);
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, NULL);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	return 0;
}