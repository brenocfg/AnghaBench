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
typedef  scalar_t__ u64 ;
struct nvme_ctrl {scalar_t__ ps_max_latency_us; } ;
struct device {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  PM_QOS_LATENCY_ANY 129 
#define  PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT 128 
 scalar_t__ U64_MAX ; 
 struct nvme_ctrl* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nvme_configure_apst (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_set_latency_tolerance(struct device *dev, s32 val)
{
	struct nvme_ctrl *ctrl = dev_get_drvdata(dev);
	u64 latency;

	switch (val) {
	case PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT:
	case PM_QOS_LATENCY_ANY:
		latency = U64_MAX;
		break;

	default:
		latency = val;
	}

	if (ctrl->ps_max_latency_us != latency) {
		ctrl->ps_max_latency_us = latency;
		nvme_configure_apst(ctrl);
	}
}