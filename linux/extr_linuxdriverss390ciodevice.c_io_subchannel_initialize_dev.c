#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_1__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_3__ schid; TYPE_2__ schib; } ;
struct TYPE_13__ {int initialized; } ;
struct TYPE_12__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct ccw_device_private {TYPE_5__ flags; TYPE_4__ dev_id; int /*<<< orphan*/  onoff; int /*<<< orphan*/  timer; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  cmb_list; int /*<<< orphan*/  todo_work; int /*<<< orphan*/  state; int /*<<< orphan*/  int_class; struct ccw_device* cdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct ccw_device {TYPE_6__ dev; struct ccw_device_private* private; int /*<<< orphan*/  ccwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_NOT_OPER ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQIO_CIO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_release ; 
 int /*<<< orphan*/  ccw_device_timeout ; 
 int /*<<< orphan*/  ccw_device_todo ; 
 int /*<<< orphan*/  ccwdev_attr_groups ; 
 int dev_set_name (TYPE_6__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_6__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_6__*) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_subchannel_initialize_dev(struct subchannel *sch,
					struct ccw_device *cdev)
{
	struct ccw_device_private *priv = cdev->private;
	int ret;

	priv->cdev = cdev;
	priv->int_class = IRQIO_CIO;
	priv->state = DEV_STATE_NOT_OPER;
	priv->dev_id.devno = sch->schib.pmcw.dev;
	priv->dev_id.ssid = sch->schid.ssid;

	INIT_WORK(&priv->todo_work, ccw_device_todo);
	INIT_LIST_HEAD(&priv->cmb_list);
	init_waitqueue_head(&priv->wait_q);
	timer_setup(&priv->timer, ccw_device_timeout, 0);

	atomic_set(&priv->onoff, 0);
	cdev->ccwlock = sch->lock;
	cdev->dev.parent = &sch->dev;
	cdev->dev.release = ccw_device_release;
	cdev->dev.groups = ccwdev_attr_groups;
	/* Do first half of device_register. */
	device_initialize(&cdev->dev);
	ret = dev_set_name(&cdev->dev, "0.%x.%04x", cdev->private->dev_id.ssid,
			   cdev->private->dev_id.devno);
	if (ret)
		goto out_put;
	if (!get_device(&sch->dev)) {
		ret = -ENODEV;
		goto out_put;
	}
	priv->flags.initialized = 1;
	spin_lock_irq(sch->lock);
	sch_set_cdev(sch, cdev);
	spin_unlock_irq(sch->lock);
	return 0;

out_put:
	/* Release reference from device_initialize(). */
	put_device(&cdev->dev);
	return ret;
}