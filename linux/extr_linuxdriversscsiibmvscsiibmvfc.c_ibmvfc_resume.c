#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vio_dev {int dummy; } ;
struct ibmvfc_host {TYPE_1__* host; int /*<<< orphan*/  tasklet; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 struct ibmvfc_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 
 int /*<<< orphan*/  vio_disable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int ibmvfc_resume(struct device *dev)
{
	unsigned long flags;
	struct ibmvfc_host *vhost = dev_get_drvdata(dev);
	struct vio_dev *vdev = to_vio_dev(dev);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	vio_disable_interrupts(vdev);
	tasklet_schedule(&vhost->tasklet);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	return 0;
}