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
struct nvme_ns {int ana_state; TYPE_1__* head; int /*<<< orphan*/  flags; int /*<<< orphan*/  ana_grpid; } ;
struct nvme_ana_group_desc {int state; int /*<<< orphan*/  grpid; } ;
typedef  enum nvme_ana_state { ____Placeholder_nvme_ana_state } nvme_ana_state ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_NS_ANA_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_mpath_set_live (struct nvme_ns*) ; 
 scalar_t__ nvme_state_is_live (int) ; 

__attribute__((used)) static void nvme_update_ns_ana_state(struct nvme_ana_group_desc *desc,
		struct nvme_ns *ns)
{
	enum nvme_ana_state old;

	mutex_lock(&ns->head->lock);
	old = ns->ana_state;
	ns->ana_grpid = le32_to_cpu(desc->grpid);
	ns->ana_state = desc->state;
	clear_bit(NVME_NS_ANA_PENDING, &ns->flags);

	if (nvme_state_is_live(ns->ana_state) && !nvme_state_is_live(old))
		nvme_mpath_set_live(ns);
	mutex_unlock(&ns->head->lock);
}