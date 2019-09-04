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
typedef  int u32 ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  fw_act_work; int /*<<< orphan*/  events; } ;

/* Variables and functions */
#define  NVME_AER_NOTICE_FW_ACT_STARTING 129 
#define  NVME_AER_NOTICE_NS_CHANGED 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvme_queue_scan (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_handle_aen_notice(struct nvme_ctrl *ctrl, u32 result)
{
	switch ((result & 0xff00) >> 8) {
	case NVME_AER_NOTICE_NS_CHANGED:
		set_bit(NVME_AER_NOTICE_NS_CHANGED, &ctrl->events);
		nvme_queue_scan(ctrl);
		break;
	case NVME_AER_NOTICE_FW_ACT_STARTING:
		queue_work(nvme_wq, &ctrl->fw_act_work);
		break;
#ifdef CONFIG_NVME_MULTIPATH
	case NVME_AER_NOTICE_ANA:
		if (!ctrl->ana_log_buf)
			break;
		queue_work(nvme_wq, &ctrl->ana_work);
		break;
#endif
	default:
		dev_warn(ctrl->device, "async event result %08x\n", result);
	}
}