#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sli4_wcqe_xri_aborted {int dummy; } ;
struct lpfc_wcqe_release {int dummy; } ;
struct lpfc_wcqe_complete {int dummy; } ;
struct lpfc_rcqe {int dummy; } ;
struct lpfc_queue {int dummy; } ;
struct lpfc_hba {void* last_completion_time; } ;
struct lpfc_cqe {int dummy; } ;

/* Variables and functions */
#define  CQE_CODE_COMPL_WQE 132 
#define  CQE_CODE_RECEIVE 131 
#define  CQE_CODE_RECEIVE_V1 130 
#define  CQE_CODE_RELEASE_WQE 129 
#define  CQE_CODE_XRI_ABORTED 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_cqe*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  lpfc_cqe_code ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli4_pcimem_bcopy (struct lpfc_cqe*,struct lpfc_cqe*,int) ; 
 int lpfc_sli4_sp_handle_abort_xri_wcqe (struct lpfc_hba*,struct lpfc_queue*,struct sli4_wcqe_xri_aborted*) ; 
 int lpfc_sli4_sp_handle_els_wcqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_wcqe_complete*) ; 
 int lpfc_sli4_sp_handle_rcqe (struct lpfc_hba*,struct lpfc_rcqe*) ; 
 int /*<<< orphan*/  lpfc_sli4_sp_handle_rel_wcqe (struct lpfc_hba*,struct lpfc_wcqe_release*) ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_cqe(struct lpfc_hba *phba, struct lpfc_queue *cq,
			 struct lpfc_cqe *cqe)
{
	struct lpfc_cqe cqevt;
	bool workposted = false;

	/* Copy the work queue CQE and convert endian order if needed */
	lpfc_sli4_pcimem_bcopy(cqe, &cqevt, sizeof(struct lpfc_cqe));

	/* Check and process for different type of WCQE and dispatch */
	switch (bf_get(lpfc_cqe_code, &cqevt)) {
	case CQE_CODE_COMPL_WQE:
		/* Process the WQ/RQ complete event */
		phba->last_completion_time = jiffies;
		workposted = lpfc_sli4_sp_handle_els_wcqe(phba, cq,
				(struct lpfc_wcqe_complete *)&cqevt);
		break;
	case CQE_CODE_RELEASE_WQE:
		/* Process the WQ release event */
		lpfc_sli4_sp_handle_rel_wcqe(phba,
				(struct lpfc_wcqe_release *)&cqevt);
		break;
	case CQE_CODE_XRI_ABORTED:
		/* Process the WQ XRI abort event */
		phba->last_completion_time = jiffies;
		workposted = lpfc_sli4_sp_handle_abort_xri_wcqe(phba, cq,
				(struct sli4_wcqe_xri_aborted *)&cqevt);
		break;
	case CQE_CODE_RECEIVE:
	case CQE_CODE_RECEIVE_V1:
		/* Process the RQ event */
		phba->last_completion_time = jiffies;
		workposted = lpfc_sli4_sp_handle_rcqe(phba,
				(struct lpfc_rcqe *)&cqevt);
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0388 Not a valid WCQE code: x%x\n",
				bf_get(lpfc_cqe_code, &cqevt));
		break;
	}
	return workposted;
}