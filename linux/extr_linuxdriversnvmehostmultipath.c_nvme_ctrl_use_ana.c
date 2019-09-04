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
struct nvme_ctrl {TYPE_1__* subsys; } ;
struct TYPE_2__ {int cmic; } ;

/* Variables and functions */
 scalar_t__ multipath ; 

inline bool nvme_ctrl_use_ana(struct nvme_ctrl *ctrl)
{
	return multipath && ctrl->subsys && (ctrl->subsys->cmic & (1 << 3));
}