#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {scalar_t__ port_state; } ;
struct TYPE_13__ {int fcf_flag; int /*<<< orphan*/  fcfi; } ;
struct lpfc_hba {int hba_flag; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  hbalock; TYPE_5__ fcf; } ;
struct TYPE_10__ {int /*<<< orphan*/  reg_fcfi; } ;
struct TYPE_11__ {TYPE_2__ un; } ;
struct TYPE_9__ {scalar_t__ mbxStatus; } ;
struct TYPE_12__ {TYPE_3__ mqe; TYPE_1__ mb; } ;
struct TYPE_14__ {TYPE_4__ u; struct lpfc_vport* vport; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FCF_IN_USE ; 
 int FCF_REGISTERED ; 
 int FCF_RR_INPROG ; 
 int FCF_SCAN_DONE ; 
 int FCF_TS_INPROG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 scalar_t__ LPFC_FLOGI ; 
 int /*<<< orphan*/  LPFC_UNREG_FCF ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_check_pending_fcoe_event (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_init_vfi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_reg_fcfi_fcfi ; 
 int /*<<< orphan*/  mempool_free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_reg_fcfi(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	struct lpfc_vport *vport = mboxq->vport;

	if (mboxq->u.mb.mbxStatus) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
			 "2017 REG_FCFI mbxStatus error x%x "
			 "HBA state x%x\n",
			 mboxq->u.mb.mbxStatus, vport->port_state);
		goto fail_out;
	}

	/* Start FCoE discovery by sending a FLOGI. */
	phba->fcf.fcfi = bf_get(lpfc_reg_fcfi_fcfi, &mboxq->u.mqe.un.reg_fcfi);
	/* Set the FCFI registered flag */
	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag |= FCF_REGISTERED;
	spin_unlock_irq(&phba->hbalock);

	/* If there is a pending FCoE event, restart FCF table scan. */
	if ((!(phba->hba_flag & FCF_RR_INPROG)) &&
		lpfc_check_pending_fcoe_event(phba, LPFC_UNREG_FCF))
		goto fail_out;

	/* Mark successful completion of FCF table scan */
	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag |= (FCF_SCAN_DONE | FCF_IN_USE);
	phba->hba_flag &= ~FCF_TS_INPROG;
	if (vport->port_state != LPFC_FLOGI) {
		phba->hba_flag |= FCF_RR_INPROG;
		spin_unlock_irq(&phba->hbalock);
		lpfc_issue_init_vfi(vport);
		goto out;
	}
	spin_unlock_irq(&phba->hbalock);
	goto out;

fail_out:
	spin_lock_irq(&phba->hbalock);
	phba->hba_flag &= ~FCF_RR_INPROG;
	spin_unlock_irq(&phba->hbalock);
out:
	mempool_free(mboxq, phba->mbox_mem_pool);
}