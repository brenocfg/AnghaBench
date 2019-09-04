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
struct lpfc_nvmet_rcv_ctx {int flag; int /*<<< orphan*/  list; int /*<<< orphan*/  oxid; } ;
struct TYPE_2__ {int /*<<< orphan*/  abts_nvme_buf_list_lock; int /*<<< orphan*/  lpfc_abts_nvmet_ctx_list; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int LPFC_NVMET_CTX_RLS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
lpfc_nvmet_defer_release(struct lpfc_hba *phba, struct lpfc_nvmet_rcv_ctx *ctxp)
{
	unsigned long iflag;

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6313 NVMET Defer ctx release xri x%x flg x%x\n",
			ctxp->oxid, ctxp->flag);

	spin_lock_irqsave(&phba->sli4_hba.abts_nvme_buf_list_lock, iflag);
	if (ctxp->flag & LPFC_NVMET_CTX_RLS) {
		spin_unlock_irqrestore(&phba->sli4_hba.abts_nvme_buf_list_lock,
				       iflag);
		return;
	}
	ctxp->flag |= LPFC_NVMET_CTX_RLS;
	list_add_tail(&ctxp->list, &phba->sli4_hba.lpfc_abts_nvmet_ctx_list);
	spin_unlock_irqrestore(&phba->sli4_hba.abts_nvme_buf_list_lock, iflag);
}