#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvme_fc_fcp_op {int /*<<< orphan*/  fcp_req; TYPE_4__* queue; int /*<<< orphan*/  state; } ;
struct nvme_fc_ctrl {int flags; TYPE_3__* rport; TYPE_2__* lport; int /*<<< orphan*/  lock; int /*<<< orphan*/  iocnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  lldd_handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  remoteport; } ;
struct TYPE_6__ {int /*<<< orphan*/  localport; TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fcp_abort ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ECANCELED ; 
 int FCCTRL_TERMIO ; 
 int /*<<< orphan*/  FCPOP_STATE_ABORTED ; 
 int FCPOP_STATE_ACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__nvme_fc_abort_op(struct nvme_fc_ctrl *ctrl, struct nvme_fc_fcp_op *op)
{
	unsigned long flags;
	int opstate;

	spin_lock_irqsave(&ctrl->lock, flags);
	opstate = atomic_xchg(&op->state, FCPOP_STATE_ABORTED);
	if (opstate != FCPOP_STATE_ACTIVE)
		atomic_set(&op->state, opstate);
	else if (ctrl->flags & FCCTRL_TERMIO)
		ctrl->iocnt++;
	spin_unlock_irqrestore(&ctrl->lock, flags);

	if (opstate != FCPOP_STATE_ACTIVE)
		return -ECANCELED;

	ctrl->lport->ops->fcp_abort(&ctrl->lport->localport,
					&ctrl->rport->remoteport,
					op->queue->lldd_handle,
					&op->fcp_req);

	return 0;
}