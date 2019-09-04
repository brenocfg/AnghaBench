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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  pam; } ;
struct TYPE_8__ {TYPE_2__ pmcw; } ;
struct subchannel {TYPE_3__ schib; } ;
struct ccw_request {int /*<<< orphan*/  callback; int /*<<< orphan*/  lpm; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  timeout; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__* private; TYPE_1__ dev; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_9__ {scalar_t__ mpath; } ;
struct TYPE_10__ {TYPE_4__ flags; int /*<<< orphan*/  path_noirq_mask; int /*<<< orphan*/  pgid_valid_mask; struct ccw_request req; struct ccw_dev_id dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGID_RETRIES ; 
 int /*<<< orphan*/  PGID_TIMEOUT ; 
 int /*<<< orphan*/  SPID_FUNC_DISBAND ; 
 int /*<<< orphan*/  SPID_FUNC_MULTI_PATH ; 
 int /*<<< orphan*/  ccw_request_start (struct ccw_device*) ; 
 int /*<<< orphan*/  memset (struct ccw_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgid_wipeout_callback ; 
 int /*<<< orphan*/  spid_build_cp (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pgid_wipeout_start(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_dev_id *id = &cdev->private->dev_id;
	struct ccw_request *req = &cdev->private->req;
	u8 fn;

	CIO_MSG_EVENT(2, "wipe: device 0.%x.%04x: pvm=%02x nim=%02x\n",
		      id->ssid, id->devno, cdev->private->pgid_valid_mask,
		      cdev->private->path_noirq_mask);

	/* Initialize request data. */
	memset(req, 0, sizeof(*req));
	req->timeout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam;
	req->callback	= pgid_wipeout_callback;
	fn = SPID_FUNC_DISBAND;
	if (cdev->private->flags.mpath)
		fn |= SPID_FUNC_MULTI_PATH;
	spid_build_cp(cdev, fn);
	ccw_request_start(cdev);
}