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
 int EBUSY ; 
 int /*<<< orphan*/  NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_delete_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nvme_delete_ctrl(struct nvme_ctrl *ctrl)
{
	if (!nvme_change_ctrl_state(ctrl, NVME_CTRL_DELETING))
		return -EBUSY;
	if (!queue_work(nvme_delete_wq, &ctrl->delete_work))
		return -EBUSY;
	return 0;
}