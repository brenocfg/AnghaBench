#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipr_ioa_cfg {int hrrq_num; TYPE_1__* hrrq; } ;
struct ipr_cmnd {int /*<<< orphan*/  done; TYPE_2__* hrrq; int /*<<< orphan*/  queue; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  hrrq_pending_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  _lock; scalar_t__ allow_interrupts; } ;

/* Variables and functions */
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ipr_reset_freeze(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	int i;

	/* Disallow new interrupts, avoid loop */
	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_interrupts = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}
	wmb();
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
	ipr_cmd->done = ipr_reset_ioa_job;
	return IPR_RC_JOB_RETURN;
}