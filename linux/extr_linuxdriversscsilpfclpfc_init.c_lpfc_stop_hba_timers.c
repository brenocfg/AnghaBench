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
struct TYPE_2__ {int /*<<< orphan*/  mbox_tmo; } ;
struct lpfc_hba {scalar_t__ sli_rev; int pci_dev_grp; int /*<<< orphan*/  fcp_poll_timer; scalar_t__ hb_outstanding; int /*<<< orphan*/  hba_flag; int /*<<< orphan*/  rrq_tmr; int /*<<< orphan*/  hb_tmofunc; int /*<<< orphan*/  eratt_poll; int /*<<< orphan*/  fabric_block_timer; TYPE_1__ sli; int /*<<< orphan*/  pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_RRQ_ACTIVE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli4_stop_fcf_redisc_wait_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_vport_timers (int /*<<< orphan*/ ) ; 

void
lpfc_stop_hba_timers(struct lpfc_hba *phba)
{
	lpfc_stop_vport_timers(phba->pport);
	del_timer_sync(&phba->sli.mbox_tmo);
	del_timer_sync(&phba->fabric_block_timer);
	del_timer_sync(&phba->eratt_poll);
	del_timer_sync(&phba->hb_tmofunc);
	if (phba->sli_rev == LPFC_SLI_REV4) {
		del_timer_sync(&phba->rrq_tmr);
		phba->hba_flag &= ~HBA_RRQ_ACTIVE;
	}
	phba->hb_outstanding = 0;

	switch (phba->pci_dev_grp) {
	case LPFC_PCI_DEV_LP:
		/* Stop any LightPulse device specific driver timers */
		del_timer_sync(&phba->fcp_poll_timer);
		break;
	case LPFC_PCI_DEV_OC:
		/* Stop any OneConnect device sepcific driver timers */
		lpfc_sli4_stop_fcf_redisc_wait_timer(phba);
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0297 Invalid device group (x%x)\n",
				phba->pci_dev_grp);
		break;
	}
	return;
}