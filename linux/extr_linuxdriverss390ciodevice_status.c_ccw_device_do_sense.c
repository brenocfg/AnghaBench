#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct irb {int /*<<< orphan*/  scsw; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_3__ dev; } ;
struct ccw1 {int /*<<< orphan*/  flags; int /*<<< orphan*/  count; scalar_t__ cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_8__ {struct ccw1 sense_ccw; } ;
struct TYPE_5__ {int /*<<< orphan*/  ecw; } ;
struct TYPE_6__ {TYPE_1__ irb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_BASIC_SENSE ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DEV_EVENT_VERIFY ; 
 int EACCES ; 
 int EBUSY ; 
 int ENODEV ; 
 int SCSW_ACTL_DEVACT ; 
 int SCSW_ACTL_SCHACT ; 
 int /*<<< orphan*/  SENSE_MAX_COUNT ; 
 scalar_t__ __pa (int /*<<< orphan*/ ) ; 
 int cio_start (struct subchannel*,struct ccw1*,int) ; 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int scsw_actl (int /*<<< orphan*/ *) ; 
 TYPE_4__* to_io_private (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int
ccw_device_do_sense(struct ccw_device *cdev, struct irb *irb)
{
	struct subchannel *sch;
	struct ccw1 *sense_ccw;
	int rc;

	sch = to_subchannel(cdev->dev.parent);

	/* A sense is required, can we do it now ? */
	if (scsw_actl(&irb->scsw) & (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT))
		/*
		 * we received an Unit Check but we have no final
		 *  status yet, therefore we must delay the SENSE
		 *  processing. We must not report this intermediate
		 *  status to the device interrupt handler.
		 */
		return -EBUSY;

	/*
	 * We have ending status but no sense information. Do a basic sense.
	 */
	sense_ccw = &to_io_private(sch)->sense_ccw;
	sense_ccw->cmd_code = CCW_CMD_BASIC_SENSE;
	sense_ccw->cda = (__u32) __pa(cdev->private->irb.ecw);
	sense_ccw->count = SENSE_MAX_COUNT;
	sense_ccw->flags = CCW_FLAG_SLI;

	rc = cio_start(sch, sense_ccw, 0xff);
	if (rc == -ENODEV || rc == -EACCES)
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
	return rc;
}