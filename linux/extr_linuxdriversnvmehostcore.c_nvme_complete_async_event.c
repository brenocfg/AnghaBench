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
union nvme_result {int /*<<< orphan*/  u32; } ;
typedef  int u32 ;
struct nvme_ctrl {int aen_result; int /*<<< orphan*/  async_event_work; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  NVME_AER_CSS 132 
#define  NVME_AER_ERROR 131 
#define  NVME_AER_NOTICE 130 
#define  NVME_AER_SMART 129 
#define  NVME_AER_VS 128 
 int NVME_SC_SUCCESS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_handle_aen_notice (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nvme_complete_async_event(struct nvme_ctrl *ctrl, __le16 status,
		volatile union nvme_result *res)
{
	u32 result = le32_to_cpu(res->u32);

	if (le16_to_cpu(status) >> 1 != NVME_SC_SUCCESS)
		return;

	switch (result & 0x7) {
	case NVME_AER_NOTICE:
		nvme_handle_aen_notice(ctrl, result);
		break;
	case NVME_AER_ERROR:
	case NVME_AER_SMART:
	case NVME_AER_CSS:
	case NVME_AER_VS:
		ctrl->aen_result = result;
		break;
	default:
		break;
	}
	queue_work(nvme_wq, &ctrl->async_event_work);
}