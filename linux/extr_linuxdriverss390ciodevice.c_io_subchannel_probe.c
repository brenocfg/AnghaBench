#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_2__ schid; TYPE_1__ dev; } ;
struct io_subchannel_private {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  SCH_TODO_UNREG ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int ccw_device_add (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_init_count ; 
 int /*<<< orphan*/  ccw_device_init_wq ; 
 int cio_commit_config (struct subchannel*) ; 
 scalar_t__ cio_is_console (TYPE_2__) ; 
 int /*<<< orphan*/  css_sched_sch_todo (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_schedule_eval (TYPE_2__) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_subchannel_attr_group ; 
 int /*<<< orphan*/  io_subchannel_init_fields (struct subchannel*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct io_subchannel_private* kzalloc (int,int) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  set_io_private (struct subchannel*,struct io_subchannel_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_subchannel_probe(struct subchannel *sch)
{
	struct io_subchannel_private *io_priv;
	struct ccw_device *cdev;
	int rc;

	if (cio_is_console(sch->schid)) {
		rc = sysfs_create_group(&sch->dev.kobj,
					&io_subchannel_attr_group);
		if (rc)
			CIO_MSG_EVENT(0, "Failed to create io subchannel "
				      "attributes for subchannel "
				      "0.%x.%04x (rc=%d)\n",
				      sch->schid.ssid, sch->schid.sch_no, rc);
		/*
		 * The console subchannel already has an associated ccw_device.
		 * Throw the delayed uevent for the subchannel, register
		 * the ccw_device and exit.
		 */
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
		cdev = sch_get_cdev(sch);
		rc = ccw_device_add(cdev);
		if (rc) {
			/* Release online reference. */
			put_device(&cdev->dev);
			goto out_schedule;
		}
		if (atomic_dec_and_test(&ccw_device_init_count))
			wake_up(&ccw_device_init_wq);
		return 0;
	}
	io_subchannel_init_fields(sch);
	rc = cio_commit_config(sch);
	if (rc)
		goto out_schedule;
	rc = sysfs_create_group(&sch->dev.kobj,
				&io_subchannel_attr_group);
	if (rc)
		goto out_schedule;
	/* Allocate I/O subchannel private data. */
	io_priv = kzalloc(sizeof(*io_priv), GFP_KERNEL | GFP_DMA);
	if (!io_priv)
		goto out_schedule;

	set_io_private(sch, io_priv);
	css_schedule_eval(sch->schid);
	return 0;

out_schedule:
	spin_lock_irq(sch->lock);
	css_sched_sch_todo(sch, SCH_TODO_UNREG);
	spin_unlock_irq(sch->lock);
	return 0;
}