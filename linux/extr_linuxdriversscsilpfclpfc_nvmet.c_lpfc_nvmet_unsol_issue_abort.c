#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int abort_tag; } ;
struct TYPE_8__ {TYPE_5__ wqe_com; TYPE_5__ wge_ctl; } ;
union lpfc_wqe128 {TYPE_3__ xmit_sequence; } ;
typedef  union lpfc_wqe {int dummy; } lpfc_wqe ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_abort_rsp_error; } ;
struct lpfc_nvmet_rcv_ctx {struct lpfc_iocbq* wqeq; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; size_t nlp_rpi; } ;
struct TYPE_9__ {int ulpLe; int /*<<< orphan*/  ulpCommand; } ;
struct lpfc_iocbq {int sli4_xritag; int iotag; TYPE_4__ iocb; scalar_t__ rsvd2; int /*<<< orphan*/ * context3; struct lpfc_nvmet_rcv_ctx* context2; struct lpfc_nodelist* context1; int /*<<< orphan*/  vport; union lpfc_wqe128 wqe; } ;
struct TYPE_7__ {int* rpi_ids; } ;
struct lpfc_hba {int /*<<< orphan*/  pport; TYPE_2__ sli4_hba; TYPE_1__* targetport; } ;
struct TYPE_6__ {scalar_t__ private; } ;

/* Variables and functions */
 int CLASS3 ; 
 int /*<<< orphan*/  CMD_XMIT_SEQUENCE64_CR ; 
 int CMD_XMIT_SEQUENCE64_WQE ; 
 int FC_RCTL_BA_ABTS ; 
 int FC_TYPE_BLS ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int LPFC_WQE_CQ_ID_DEFAULT ; 
 int LPFC_WQE_IOD_WRITE ; 
 int LPFC_WQE_LENLOC_WORD12 ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ NLP_STE_MAX_STATE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int OTHER_COMMAND ; 
 int SLI4_CT_RPI ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 struct lpfc_nodelist* lpfc_findnode_did (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wqe_class ; 
 int /*<<< orphan*/  wqe_cmd_type ; 
 int /*<<< orphan*/  wqe_cmnd ; 
 int /*<<< orphan*/  wqe_cqid ; 
 int /*<<< orphan*/  wqe_ct ; 
 int /*<<< orphan*/  wqe_ctxt_tag ; 
 int /*<<< orphan*/  wqe_dbde ; 
 int /*<<< orphan*/  wqe_dfctl ; 
 int /*<<< orphan*/  wqe_ebde_cnt ; 
 int /*<<< orphan*/  wqe_iod ; 
 int /*<<< orphan*/  wqe_la ; 
 int /*<<< orphan*/  wqe_lenloc ; 
 int /*<<< orphan*/  wqe_ls ; 
 int /*<<< orphan*/  wqe_pu ; 
 int /*<<< orphan*/  wqe_qosd ; 
 int /*<<< orphan*/  wqe_rctl ; 
 int /*<<< orphan*/  wqe_rcvoxid ; 
 int /*<<< orphan*/  wqe_reqtag ; 
 int /*<<< orphan*/  wqe_type ; 
 int /*<<< orphan*/  wqe_xri_tag ; 

__attribute__((used)) static int
lpfc_nvmet_unsol_issue_abort(struct lpfc_hba *phba,
			     struct lpfc_nvmet_rcv_ctx *ctxp,
			     uint32_t sid, uint16_t xri)
{
	struct lpfc_nvmet_tgtport *tgtp;
	struct lpfc_iocbq *abts_wqeq;
	union lpfc_wqe128 *wqe_abts;
	struct lpfc_nodelist *ndlp;

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6067 ABTS: sid %x xri x%x/x%x\n",
			sid, xri, ctxp->wqeq->sli4_xritag);

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;

	ndlp = lpfc_findnode_did(phba->pport, sid);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp) ||
	    ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE))) {
		atomic_inc(&tgtp->xmt_abort_rsp_error);
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_ABTS,
				"6134 Drop ABTS - wrong NDLP state x%x.\n",
				(ndlp) ? ndlp->nlp_state : NLP_STE_MAX_STATE);

		/* No failure to an ABTS request. */
		return 0;
	}

	abts_wqeq = ctxp->wqeq;
	wqe_abts = &abts_wqeq->wqe;

	/*
	 * Since we zero the whole WQE, we need to ensure we set the WQE fields
	 * that were initialized in lpfc_sli4_nvmet_alloc.
	 */
	memset(wqe_abts, 0, sizeof(union lpfc_wqe));

	/* Word 5 */
	bf_set(wqe_dfctl, &wqe_abts->xmit_sequence.wge_ctl, 0);
	bf_set(wqe_ls, &wqe_abts->xmit_sequence.wge_ctl, 1);
	bf_set(wqe_la, &wqe_abts->xmit_sequence.wge_ctl, 0);
	bf_set(wqe_rctl, &wqe_abts->xmit_sequence.wge_ctl, FC_RCTL_BA_ABTS);
	bf_set(wqe_type, &wqe_abts->xmit_sequence.wge_ctl, FC_TYPE_BLS);

	/* Word 6 */
	bf_set(wqe_ctxt_tag, &wqe_abts->xmit_sequence.wqe_com,
	       phba->sli4_hba.rpi_ids[ndlp->nlp_rpi]);
	bf_set(wqe_xri_tag, &wqe_abts->xmit_sequence.wqe_com,
	       abts_wqeq->sli4_xritag);

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe_abts->xmit_sequence.wqe_com,
	       CMD_XMIT_SEQUENCE64_WQE);
	bf_set(wqe_ct, &wqe_abts->xmit_sequence.wqe_com, SLI4_CT_RPI);
	bf_set(wqe_class, &wqe_abts->xmit_sequence.wqe_com, CLASS3);
	bf_set(wqe_pu, &wqe_abts->xmit_sequence.wqe_com, 0);

	/* Word 8 */
	wqe_abts->xmit_sequence.wqe_com.abort_tag = abts_wqeq->iotag;

	/* Word 9 */
	bf_set(wqe_reqtag, &wqe_abts->xmit_sequence.wqe_com, abts_wqeq->iotag);
	/* Needs to be set by caller */
	bf_set(wqe_rcvoxid, &wqe_abts->xmit_sequence.wqe_com, xri);

	/* Word 10 */
	bf_set(wqe_dbde, &wqe_abts->xmit_sequence.wqe_com, 1);
	bf_set(wqe_iod, &wqe_abts->xmit_sequence.wqe_com, LPFC_WQE_IOD_WRITE);
	bf_set(wqe_lenloc, &wqe_abts->xmit_sequence.wqe_com,
	       LPFC_WQE_LENLOC_WORD12);
	bf_set(wqe_ebde_cnt, &wqe_abts->xmit_sequence.wqe_com, 0);
	bf_set(wqe_qosd, &wqe_abts->xmit_sequence.wqe_com, 0);

	/* Word 11 */
	bf_set(wqe_cqid, &wqe_abts->xmit_sequence.wqe_com,
	       LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_cmd_type, &wqe_abts->xmit_sequence.wqe_com,
	       OTHER_COMMAND);

	abts_wqeq->vport = phba->pport;
	abts_wqeq->context1 = ndlp;
	abts_wqeq->context2 = ctxp;
	abts_wqeq->context3 = NULL;
	abts_wqeq->rsvd2 = 0;
	/* hba_wqidx should already be setup from command we are aborting */
	abts_wqeq->iocb.ulpCommand = CMD_XMIT_SEQUENCE64_CR;
	abts_wqeq->iocb.ulpLe = 1;

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6069 Issue ABTS to xri x%x reqtag x%x\n",
			xri, abts_wqeq->iotag);
	return 1;
}