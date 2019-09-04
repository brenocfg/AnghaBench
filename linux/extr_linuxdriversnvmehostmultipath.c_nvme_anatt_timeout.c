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
struct timer_list {int dummy; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  anatt_timer ; 
 struct nvme_ctrl* ctrl ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct nvme_ctrl* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_reset_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_anatt_timeout(struct timer_list *t)
{
	struct nvme_ctrl *ctrl = from_timer(ctrl, t, anatt_timer);

	dev_info(ctrl->device, "ANATT timeout, resetting controller.\n");
	nvme_reset_ctrl(ctrl);
}