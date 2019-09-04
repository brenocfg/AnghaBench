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
struct lpfc_sli_ring {int dummy; } ;
struct lpfc_iocbq {int iocb_flag; int hba_wqidx; int /*<<< orphan*/  context1; } ;
struct TYPE_8__ {TYPE_3__* els_wq; TYPE_2__* oas_wq; TYPE_1__** fcp_wq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; TYPE_4__ sli4_hba; int /*<<< orphan*/  cfg_fof; } ;
struct TYPE_7__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_6__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_5__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 int LPFC_IO_FCP ; 
 int LPFC_IO_FOF ; 
 int LPFC_USE_FCPWQIDX ; 
 int lpfc_sli4_scmd_to_wqidx_distr (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct lpfc_sli_ring *
lpfc_sli4_calc_ring(struct lpfc_hba *phba, struct lpfc_iocbq *piocb)
{
	if (piocb->iocb_flag & (LPFC_IO_FCP | LPFC_USE_FCPWQIDX)) {
		if (!(phba->cfg_fof) ||
		    (!(piocb->iocb_flag & LPFC_IO_FOF))) {
			if (unlikely(!phba->sli4_hba.fcp_wq))
				return NULL;
			/*
			 * for abort iocb hba_wqidx should already
			 * be setup based on what work queue we used.
			 */
			if (!(piocb->iocb_flag & LPFC_USE_FCPWQIDX)) {
				piocb->hba_wqidx =
					lpfc_sli4_scmd_to_wqidx_distr(phba,
							      piocb->context1);
				piocb->hba_wqidx = piocb->hba_wqidx %
					phba->cfg_fcp_io_channel;
			}
			return phba->sli4_hba.fcp_wq[piocb->hba_wqidx]->pring;
		} else {
			if (unlikely(!phba->sli4_hba.oas_wq))
				return NULL;
			piocb->hba_wqidx = 0;
			return phba->sli4_hba.oas_wq->pring;
		}
	} else {
		if (unlikely(!phba->sli4_hba.els_wq))
			return NULL;
		piocb->hba_wqidx = 0;
		return phba->sli4_hba.els_wq->pring;
	}
}