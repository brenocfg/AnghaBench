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
typedef  int u32 ;
struct nvme_ctrl {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* reg_read32 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int NVME_CSTS_RDY ; 
 int /*<<< orphan*/  NVME_REG_CSTS ; 
 scalar_t__ stub1 (struct nvme_ctrl*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool nvme_ctrl_ready(struct nvme_ctrl *ctrl)
{
	u32 val = 0;

	if (ctrl->ops->reg_read32(ctrl, NVME_REG_CSTS, &val))
		return false;
	return val & NVME_CSTS_RDY;
}