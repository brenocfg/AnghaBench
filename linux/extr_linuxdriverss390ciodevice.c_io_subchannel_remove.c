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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct subchannel {TYPE_1__ dev; int /*<<< orphan*/  lock; } ;
struct io_subchannel_private {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_unregister (struct ccw_device*) ; 
 int /*<<< orphan*/  io_subchannel_attr_group ; 
 int /*<<< orphan*/  kfree (struct io_subchannel_private*) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_io_private (struct subchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct io_subchannel_private* to_io_private (struct subchannel*) ; 

__attribute__((used)) static int io_subchannel_remove(struct subchannel *sch)
{
	struct io_subchannel_private *io_priv = to_io_private(sch);
	struct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (!cdev)
		goto out_free;

	ccw_device_unregister(cdev);
	spin_lock_irq(sch->lock);
	sch_set_cdev(sch, NULL);
	set_io_private(sch, NULL);
	spin_unlock_irq(sch->lock);
out_free:
	kfree(io_priv);
	sysfs_remove_group(&sch->dev.kobj, &io_subchannel_attr_group);
	return 0;
}