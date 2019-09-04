#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct device {int dummy; } ;
struct ccw_driver {int /*<<< orphan*/  (* remove ) (struct ccw_device*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_3__ dev; TYPE_2__* private; struct ccw_driver* drv; scalar_t__ online; } ;
struct TYPE_4__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_class; TYPE_1__ dev_id; int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQIO_CIO ; 
 int /*<<< orphan*/  __disable_cmf (struct ccw_device*) ; 
 int ccw_device_offline (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_fsm_final_state (struct ccw_device*) ; 
 int /*<<< orphan*/  io_subchannel_quiesce (struct subchannel*) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_remove(struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct ccw_driver *cdrv = cdev->drv;
	struct subchannel *sch;
	int ret;

	if (cdrv->remove)
		cdrv->remove(cdev);

	spin_lock_irq(cdev->ccwlock);
	if (cdev->online) {
		cdev->online = 0;
		ret = ccw_device_offline(cdev);
		spin_unlock_irq(cdev->ccwlock);
		if (ret == 0)
			wait_event(cdev->private->wait_q,
				   dev_fsm_final_state(cdev));
		else
			CIO_MSG_EVENT(0, "ccw_device_offline returned %d, "
				      "device 0.%x.%04x\n",
				      ret, cdev->private->dev_id.ssid,
				      cdev->private->dev_id.devno);
		/* Give up reference obtained in ccw_device_set_online(). */
		put_device(&cdev->dev);
		spin_lock_irq(cdev->ccwlock);
	}
	ccw_device_set_timeout(cdev, 0);
	cdev->drv = NULL;
	cdev->private->int_class = IRQIO_CIO;
	sch = to_subchannel(cdev->dev.parent);
	spin_unlock_irq(cdev->ccwlock);
	io_subchannel_quiesce(sch);
	__disable_cmf(cdev);

	return 0;
}