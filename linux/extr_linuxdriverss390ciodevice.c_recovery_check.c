#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pam; } ;
struct TYPE_8__ {TYPE_2__ pmcw; } ;
struct subchannel {int opm; int vpm; TYPE_3__ schib; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_5__* private; TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_10__ {int state; TYPE_4__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_EVENT_VERIFY ; 
#define  DEV_STATE_DISCONNECTED 130 
#define  DEV_STATE_DISCONNECTED_SENSE_ID 129 
#define  DEV_STATE_ONLINE 128 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recovery_check(struct device *dev, void *data)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct subchannel *sch;
	int *redo = data;

	spin_lock_irq(cdev->ccwlock);
	switch (cdev->private->state) {
	case DEV_STATE_ONLINE:
		sch = to_subchannel(cdev->dev.parent);
		if ((sch->schib.pmcw.pam & sch->opm) == sch->vpm)
			break;
		/* fall through */
	case DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(3, "recovery: trigger 0.%x.%04x\n",
			      cdev->private->dev_id.ssid,
			      cdev->private->dev_id.devno);
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
		*redo = 1;
		break;
	case DEV_STATE_DISCONNECTED_SENSE_ID:
		*redo = 1;
		break;
	}
	spin_unlock_irq(cdev->ccwlock);

	return 0;
}