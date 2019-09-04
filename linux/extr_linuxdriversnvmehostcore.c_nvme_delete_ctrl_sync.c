#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvme_ctrl {int /*<<< orphan*/  delete_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int nvme_delete_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_get_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_put_ctrl (struct nvme_ctrl*) ; 

int nvme_delete_ctrl_sync(struct nvme_ctrl *ctrl)
{
	int ret = 0;

	/*
	 * Keep a reference until the work is flushed since ->delete_ctrl
	 * can free the controller.
	 */
	nvme_get_ctrl(ctrl);
	ret = nvme_delete_ctrl(ctrl);
	if (!ret)
		flush_work(&ctrl->delete_work);
	nvme_put_ctrl(ctrl);
	return ret;
}