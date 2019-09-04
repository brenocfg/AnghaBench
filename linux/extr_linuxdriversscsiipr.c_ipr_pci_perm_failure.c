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
struct pci_dev {int dummy; } ;
struct ipr_ioa_cfg {scalar_t__ sdt_state; int in_ioa_bringdown; int hrrq_num; TYPE_2__* host; int /*<<< orphan*/  eeh_wait_q; TYPE_1__* hrrq; scalar_t__ reset_retries; scalar_t__ probe_done; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  _lock; scalar_t__ allow_cmds; } ;

/* Variables and functions */
 scalar_t__ ABORT_DUMP ; 
 scalar_t__ IPR_NUM_RESET_RELOAD_RETRIES ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NONE ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 
 struct ipr_ioa_cfg* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ipr_pci_perm_failure(struct pci_dev *pdev)
{
	unsigned long flags = 0;
	struct ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);
	int i;

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	if (ioa_cfg->probe_done) {
		if (ioa_cfg->sdt_state == WAIT_FOR_DUMP)
			ioa_cfg->sdt_state = ABORT_DUMP;
		ioa_cfg->reset_retries = IPR_NUM_RESET_RELOAD_RETRIES - 1;
		ioa_cfg->in_ioa_bringdown = 1;
		for (i = 0; i < ioa_cfg->hrrq_num; i++) {
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].allow_cmds = 0;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		}
		wmb();
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	} else
		wake_up_all(&ioa_cfg->eeh_wait_q);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
}