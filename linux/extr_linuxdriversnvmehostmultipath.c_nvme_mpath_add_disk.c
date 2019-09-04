#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {TYPE_1__* head; int /*<<< orphan*/  ana_state; TYPE_2__* ctrl; int /*<<< orphan*/  ana_grpid; } ;
struct nvme_id_ns {int /*<<< orphan*/  anagrpid; } ;
struct TYPE_5__ {int /*<<< orphan*/  ana_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_ANA_OPTIMIZED ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nvme_ctrl_use_ana (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_mpath_set_live (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_parse_ana_log (TYPE_2__*,struct nvme_ns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_set_ns_ana_state ; 

void nvme_mpath_add_disk(struct nvme_ns *ns, struct nvme_id_ns *id)
{
	if (nvme_ctrl_use_ana(ns->ctrl)) {
		mutex_lock(&ns->ctrl->ana_lock);
		ns->ana_grpid = le32_to_cpu(id->anagrpid);
		nvme_parse_ana_log(ns->ctrl, ns, nvme_set_ns_ana_state);
		mutex_unlock(&ns->ctrl->ana_lock);
	} else {
		mutex_lock(&ns->head->lock);
		ns->ana_state = NVME_ANA_OPTIMIZED; 
		nvme_mpath_set_live(ns);
		mutex_unlock(&ns->head->lock);
	}
}