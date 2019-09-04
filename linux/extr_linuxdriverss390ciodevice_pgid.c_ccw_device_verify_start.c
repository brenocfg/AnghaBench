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
struct ccw_device {TYPE_3__* private; } ;
struct TYPE_5__ {scalar_t__ doverify; int /*<<< orphan*/  mpath; int /*<<< orphan*/  pgroup; } ;
struct TYPE_4__ {int /*<<< orphan*/  mpath; int /*<<< orphan*/  pgroup; } ;
struct TYPE_6__ {scalar_t__ path_noirq_mask; TYPE_2__ flags; TYPE_1__ options; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  verify_start (struct ccw_device*) ; 

void ccw_device_verify_start(struct ccw_device *cdev)
{
	CIO_TRACE_EVENT(4, "vrfy");
	CIO_HEX_EVENT(4, &cdev->private->dev_id, sizeof(cdev->private->dev_id));
	/*
	 * Initialize pathgroup and multipath state with target values.
	 * They may change in the course of path verification.
	 */
	cdev->private->flags.pgroup = cdev->private->options.pgroup;
	cdev->private->flags.mpath = cdev->private->options.mpath;
	cdev->private->flags.doverify = 0;
	cdev->private->path_noirq_mask = 0;
	verify_start(cdev);
}