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
struct nvmet_ana_group {size_t grpid; TYPE_1__* port; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ana_state; struct nvmet_ana_group ana_default_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_ANA_INACCESSIBLE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvmet_ana_group*) ; 
 int /*<<< orphan*/ * nvmet_ana_group_enabled ; 
 int /*<<< orphan*/  nvmet_ana_sem ; 
 int /*<<< orphan*/  nvmet_port_send_ana_event (TYPE_1__*) ; 
 struct nvmet_ana_group* to_ana_group (struct config_item*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_ana_group_release(struct config_item *item)
{
	struct nvmet_ana_group *grp = to_ana_group(item);

	if (grp == &grp->port->ana_default_group)
		return;

	down_write(&nvmet_ana_sem);
	grp->port->ana_state[grp->grpid] = NVME_ANA_INACCESSIBLE;
	nvmet_ana_group_enabled[grp->grpid]--;
	up_write(&nvmet_ana_sem);

	nvmet_port_send_ana_event(grp->port);
	kfree(grp);
}