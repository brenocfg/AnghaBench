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
struct nvme_id_ctrl {int dummy; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; TYPE_1__* subsys; } ;
struct TYPE_2__ {int cmic; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int nvme_mpath_init(struct nvme_ctrl *ctrl,
		struct nvme_id_ctrl *id)
{
	if (ctrl->subsys->cmic & (1 << 3))
		dev_warn(ctrl->device,
"Please enable CONFIG_NVME_MULTIPATH for full support of multi-port devices.\n");
	return 0;
}