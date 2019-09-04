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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct nvme_ctrl {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* reg_read32 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int HZ ; 
 int NVME_CAP_TIMEOUT (int /*<<< orphan*/ ) ; 
 int NVME_CSTS_RDY ; 
 int /*<<< orphan*/  NVME_REG_CSTS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct nvme_ctrl*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int nvme_wait_ready(struct nvme_ctrl *ctrl, u64 cap, bool enabled)
{
	unsigned long timeout =
		((NVME_CAP_TIMEOUT(cap) + 1) * HZ / 2) + jiffies;
	u32 csts, bit = enabled ? NVME_CSTS_RDY : 0;
	int ret;

	while ((ret = ctrl->ops->reg_read32(ctrl, NVME_REG_CSTS, &csts)) == 0) {
		if (csts == ~0)
			return -ENODEV;
		if ((csts & NVME_CSTS_RDY) == bit)
			break;

		msleep(100);
		if (fatal_signal_pending(current))
			return -EINTR;
		if (time_after(jiffies, timeout)) {
			dev_err(ctrl->device,
				"Device not ready; aborting %s\n", enabled ?
						"initialisation" : "reset");
			return -ENODEV;
		}
	}

	return ret;
}