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
struct irb {int dummy; } ;
struct ccw_request {int done; int drc; int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (struct ccw_device*,int /*<<< orphan*/ ,int) ;} ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  irb; struct ccw_request req; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ccwreq_stop(struct ccw_device *cdev, int rc)
{
	struct ccw_request *req = &cdev->private->req;

	if (req->done)
		return;
	req->done = 1;
	ccw_device_set_timeout(cdev, 0);
	memset(&cdev->private->irb, 0, sizeof(struct irb));
	if (rc && rc != -ENODEV && req->drc)
		rc = req->drc;
	req->callback(cdev, req->data, rc);
}