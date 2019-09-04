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
struct nvme_fc_lport {int /*<<< orphan*/  localport; TYPE_1__* ops; int /*<<< orphan*/  act_rport_cnt; } ;
struct nvme_fc_local_port {scalar_t__ port_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* localport_delete ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FC_OBJSTATE_DELETED ; 
 scalar_t__ FC_OBJSTATE_ONLINE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct nvme_fc_lport* localport_to_lport (struct nvme_fc_local_port*) ; 
 int /*<<< orphan*/  nvme_fc_lock ; 
 int /*<<< orphan*/  nvme_fc_lport_put (struct nvme_fc_lport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

int
nvme_fc_unregister_localport(struct nvme_fc_local_port *portptr)
{
	struct nvme_fc_lport *lport = localport_to_lport(portptr);
	unsigned long flags;

	if (!portptr)
		return -EINVAL;

	spin_lock_irqsave(&nvme_fc_lock, flags);

	if (portptr->port_state != FC_OBJSTATE_ONLINE) {
		spin_unlock_irqrestore(&nvme_fc_lock, flags);
		return -EINVAL;
	}
	portptr->port_state = FC_OBJSTATE_DELETED;

	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	if (atomic_read(&lport->act_rport_cnt) == 0)
		lport->ops->localport_delete(&lport->localport);

	nvme_fc_lport_put(lport);

	return 0;
}