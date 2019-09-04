#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pam; } ;
struct TYPE_9__ {TYPE_2__ pmcw; } ;
struct subchannel {int lpm; int opm; TYPE_3__ schib; } ;
struct TYPE_10__ {int /*<<< orphan*/  cu_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_6__* private; TYPE_4__ id; int /*<<< orphan*/  online; TYPE_1__ dev; } ;
struct TYPE_11__ {int recog_done; int donotify; scalar_t__ resuming; } ;
struct TYPE_12__ {int state; int /*<<< orphan*/  wait_q; TYPE_5__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_REBIND ; 
#define  DEV_STATE_BOXED 130 
 int DEV_STATE_DISCONNECTED ; 
 int DEV_STATE_DISCONNECTED_SENSE_ID ; 
#define  DEV_STATE_NOT_OPER 129 
#define  DEV_STATE_OFFLINE 128 
 int /*<<< orphan*/  __recover_lost_chpids (struct subchannel*,int) ; 
 int /*<<< orphan*/  ccw_device_online (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_test_sense_data (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_update_sense_data (struct ccw_device*) ; 
 scalar_t__ cio_disable_subchannel (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  io_subchannel_recog_done (struct ccw_device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ccw_device_recog_done(struct ccw_device *cdev, int state)
{
	struct subchannel *sch;
	int old_lpm;

	sch = to_subchannel(cdev->dev.parent);

	if (cio_disable_subchannel(sch))
		state = DEV_STATE_NOT_OPER;
	/*
	 * Now that we tried recognition, we have performed device selection
	 * through ssch() and the path information is up to date.
	 */
	old_lpm = sch->lpm;

	/* Check since device may again have become not operational. */
	if (cio_update_schib(sch))
		state = DEV_STATE_NOT_OPER;
	else
		sch->lpm = sch->schib.pmcw.pam & sch->opm;

	if (cdev->private->state == DEV_STATE_DISCONNECTED_SENSE_ID)
		/* Force reprobe on all chpids. */
		old_lpm = 0;
	if (sch->lpm != old_lpm)
		__recover_lost_chpids(sch, old_lpm);
	if (cdev->private->state == DEV_STATE_DISCONNECTED_SENSE_ID &&
	    (state == DEV_STATE_NOT_OPER || state == DEV_STATE_BOXED)) {
		cdev->private->flags.recog_done = 1;
		cdev->private->state = DEV_STATE_DISCONNECTED;
		wake_up(&cdev->private->wait_q);
		return;
	}
	if (cdev->private->flags.resuming) {
		cdev->private->state = state;
		cdev->private->flags.recog_done = 1;
		wake_up(&cdev->private->wait_q);
		return;
	}
	switch (state) {
	case DEV_STATE_NOT_OPER:
		break;
	case DEV_STATE_OFFLINE:
		if (!cdev->online) {
			ccw_device_update_sense_data(cdev);
			break;
		}
		cdev->private->state = DEV_STATE_OFFLINE;
		cdev->private->flags.recog_done = 1;
		if (ccw_device_test_sense_data(cdev)) {
			cdev->private->flags.donotify = 1;
			ccw_device_online(cdev);
			wake_up(&cdev->private->wait_q);
		} else {
			ccw_device_update_sense_data(cdev);
			ccw_device_sched_todo(cdev, CDEV_TODO_REBIND);
		}
		return;
	case DEV_STATE_BOXED:
		if (cdev->id.cu_type != 0) { /* device was recognized before */
			cdev->private->flags.recog_done = 1;
			cdev->private->state = DEV_STATE_BOXED;
			wake_up(&cdev->private->wait_q);
			return;
		}
		break;
	}
	cdev->private->state = state;
	io_subchannel_recog_done(cdev);
	wake_up(&cdev->private->wait_q);
}