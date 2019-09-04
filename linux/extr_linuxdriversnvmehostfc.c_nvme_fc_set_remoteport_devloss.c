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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_loss_tmo; } ;
struct nvme_fc_rport {int /*<<< orphan*/  lock; TYPE_1__ remoteport; } ;
struct nvme_fc_remote_port {scalar_t__ port_state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FC_OBJSTATE_ONLINE ; 
 struct nvme_fc_rport* remoteport_to_rport (struct nvme_fc_remote_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nvme_fc_set_remoteport_devloss(struct nvme_fc_remote_port *portptr,
			u32 dev_loss_tmo)
{
	struct nvme_fc_rport *rport = remoteport_to_rport(portptr);
	unsigned long flags;

	spin_lock_irqsave(&rport->lock, flags);

	if (portptr->port_state != FC_OBJSTATE_ONLINE) {
		spin_unlock_irqrestore(&rport->lock, flags);
		return -EINVAL;
	}

	/* a dev_loss_tmo of 0 (immediate) is allowed to be set */
	rport->remoteport.dev_loss_tmo = dev_loss_tmo;

	spin_unlock_irqrestore(&rport->lock, flags);

	return 0;
}