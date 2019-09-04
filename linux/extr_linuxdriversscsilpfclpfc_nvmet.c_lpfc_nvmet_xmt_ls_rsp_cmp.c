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
typedef  scalar_t__ uint32_t ;
struct nvmefc_tgt_ls_req {int /*<<< orphan*/  (* done ) (struct nvmefc_tgt_ls_req*) ;} ;
struct lpfc_wcqe_complete {scalar_t__ parameter; } ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_ls_rsp_cmpl; int /*<<< orphan*/  xmt_ls_rsp_xb_set; int /*<<< orphan*/  xmt_ls_rsp_aborted; int /*<<< orphan*/  xmt_ls_rsp_error; } ;
struct TYPE_4__ {struct nvmefc_tgt_ls_req ls_req; } ;
struct lpfc_nvmet_rcv_ctx {scalar_t__ state; int entry_cnt; scalar_t__ oxid; TYPE_2__ ctx; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context3; struct lpfc_nvmet_rcv_ctx* context2; int /*<<< orphan*/  context1; } ;
struct lpfc_hba {TYPE_1__* targetport; } ;
struct TYPE_3__ {scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ IOERR_ABORT_REQUESTED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 scalar_t__ LPFC_NVMET_STE_LS_RSP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvmet_rcv_ctx*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvmeio_data (struct lpfc_hba*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_status ; 
 int /*<<< orphan*/  lpfc_wcqe_c_xb ; 
 int /*<<< orphan*/  stub1 (struct nvmefc_tgt_ls_req*) ; 

__attribute__((used)) static void
lpfc_nvmet_xmt_ls_rsp_cmp(struct lpfc_hba *phba, struct lpfc_iocbq *cmdwqe,
			  struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_nvmet_tgtport *tgtp;
	struct nvmefc_tgt_ls_req *rsp;
	struct lpfc_nvmet_rcv_ctx *ctxp;
	uint32_t status, result;

	status = bf_get(lpfc_wcqe_c_status, wcqe);
	result = wcqe->parameter;
	ctxp = cmdwqe->context2;

	if (ctxp->state != LPFC_NVMET_STE_LS_RSP || ctxp->entry_cnt != 2) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6410 NVMET LS cmpl state mismatch IO x%x: "
				"%d %d\n",
				ctxp->oxid, ctxp->state, ctxp->entry_cnt);
	}

	if (!phba->targetport)
		goto out;

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;

	if (tgtp) {
		if (status) {
			atomic_inc(&tgtp->xmt_ls_rsp_error);
			if (result == IOERR_ABORT_REQUESTED)
				atomic_inc(&tgtp->xmt_ls_rsp_aborted);
			if (bf_get(lpfc_wcqe_c_xb, wcqe))
				atomic_inc(&tgtp->xmt_ls_rsp_xb_set);
		} else {
			atomic_inc(&tgtp->xmt_ls_rsp_cmpl);
		}
	}

out:
	rsp = &ctxp->ctx.ls_req;

	lpfc_nvmeio_data(phba, "NVMET LS  CMPL: xri x%x stat x%x result x%x\n",
			 ctxp->oxid, status, result);

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_DISC,
			"6038 NVMET LS rsp cmpl: %d %d oxid x%x\n",
			status, result, ctxp->oxid);

	lpfc_nlp_put(cmdwqe->context1);
	cmdwqe->context2 = NULL;
	cmdwqe->context3 = NULL;
	lpfc_sli_release_iocbq(phba, cmdwqe);
	rsp->done(rsp);
	kfree(ctxp);
}