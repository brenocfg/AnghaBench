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
struct TYPE_8__ {int lpum; int /*<<< orphan*/ * chpid; } ;
struct TYPE_9__ {TYPE_3__ pmcw; int /*<<< orphan*/  scsw; } ;
struct TYPE_7__ {int /*<<< orphan*/  cssid; } ;
struct subchannel {TYPE_4__ schib; TYPE_2__ schid; } ;
struct ccw_request {int timeout; int /*<<< orphan*/  drc; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__ dev; TYPE_1__* private; } ;
struct TYPE_6__ {struct ccw_request req; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  ccwreq_next_path (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwreq_stop (struct ccw_device*,int) ; 
 int cio_clear (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsw_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_dstat (int /*<<< orphan*/ *) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void ccw_request_timeout(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;
	int rc = -ENODEV, chp;

	if (cio_update_schib(sch))
		goto err;

	for (chp = 0; chp < 8; chp++) {
		if ((0x80 >> chp) & sch->schib.pmcw.lpum)
			pr_warn("%s: No interrupt was received within %lus (CS=%02x, DS=%02x, CHPID=%x.%02x)\n",
				dev_name(&cdev->dev), req->timeout / HZ,
				scsw_cstat(&sch->schib.scsw),
				scsw_dstat(&sch->schib.scsw),
				sch->schid.cssid,
				sch->schib.pmcw.chpid[chp]);
	}

	if (!ccwreq_next_path(cdev)) {
		/* set the final return code for this request */
		req->drc = -ETIME;
	}
	rc = cio_clear(sch);
	if (rc)
		goto err;
	return;

err:
	ccwreq_stop(cdev, rc);
}