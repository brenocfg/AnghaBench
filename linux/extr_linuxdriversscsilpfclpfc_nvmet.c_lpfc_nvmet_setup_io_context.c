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
typedef  union lpfc_wqe128 {int dummy; } lpfc_wqe128 ;
typedef  union lpfc_wqe {int dummy; } lpfc_wqe ;
struct lpfc_nvmet_ctxbuf {int /*<<< orphan*/  list; struct lpfc_nvmet_ctxbuf* context; struct lpfc_iocbq* iocbq; int /*<<< orphan*/  sglq; int /*<<< orphan*/  state; struct lpfc_nvmet_ctxbuf* ctxbuf; } ;
struct lpfc_nvmet_ctx_info {struct lpfc_nvmet_ctx_info* nvmet_ctx_next_cpu; scalar_t__ nvmet_ctx_list_cnt; int /*<<< orphan*/  nvmet_ctx_list_lock; int /*<<< orphan*/  nvmet_ctx_list; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context1; union lpfc_wqe128 wqe; int /*<<< orphan*/  iocb_flag; } ;
struct TYPE_2__ {int nvmet_xri_cnt; int num_present_cpu; struct lpfc_nvmet_ctx_info* nvmet_ctx_info; int /*<<< orphan*/  sgl_list_lock; } ;
struct lpfc_hba {int cfg_nvmet_mrq; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_INIT ; 
 int LOG_NVME ; 
 int /*<<< orphan*/  LPFC_IO_NVMET ; 
 int /*<<< orphan*/  LPFC_NVMET_STE_FREE ; 
 int /*<<< orphan*/  __lpfc_sli_get_nvmet_sglq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_nvmet_ctx_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvmet_ctxbuf*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lpfc_nvmet_ctx_info* lpfc_get_ctx_list (struct lpfc_hba*,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_nvmet_setup_io_context(struct lpfc_hba *phba)
{
	struct lpfc_nvmet_ctxbuf *ctx_buf;
	struct lpfc_iocbq *nvmewqe;
	union lpfc_wqe128 *wqe;
	struct lpfc_nvmet_ctx_info *last_infop;
	struct lpfc_nvmet_ctx_info *infop;
	int i, j, idx;

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME,
			"6403 Allocate NVMET resources for %d XRIs\n",
			phba->sli4_hba.nvmet_xri_cnt);

	phba->sli4_hba.nvmet_ctx_info = kcalloc(
		phba->sli4_hba.num_present_cpu * phba->cfg_nvmet_mrq,
		sizeof(struct lpfc_nvmet_ctx_info), GFP_KERNEL);
	if (!phba->sli4_hba.nvmet_ctx_info) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"6419 Failed allocate memory for "
				"nvmet context lists\n");
		return -ENOMEM;
	}

	/*
	 * Assuming X CPUs in the system, and Y MRQs, allocate some
	 * lpfc_nvmet_ctx_info structures as follows:
	 *
	 * cpu0/mrq0 cpu1/mrq0 ... cpuX/mrq0
	 * cpu0/mrq1 cpu1/mrq1 ... cpuX/mrq1
	 * ...
	 * cpuX/mrqY cpuX/mrqY ... cpuX/mrqY
	 *
	 * Each line represents a MRQ "silo" containing an entry for
	 * every CPU.
	 *
	 * MRQ X is initially assumed to be associated with CPU X, thus
	 * contexts are initially distributed across all MRQs using
	 * the MRQ index (N) as follows cpuN/mrqN. When contexts are
	 * freed, the are freed to the MRQ silo based on the CPU number
	 * of the IO completion. Thus a context that was allocated for MRQ A
	 * whose IO completed on CPU B will be freed to cpuB/mrqA.
	 */
	infop = phba->sli4_hba.nvmet_ctx_info;
	for (i = 0; i < phba->sli4_hba.num_present_cpu; i++) {
		for (j = 0; j < phba->cfg_nvmet_mrq; j++) {
			INIT_LIST_HEAD(&infop->nvmet_ctx_list);
			spin_lock_init(&infop->nvmet_ctx_list_lock);
			infop->nvmet_ctx_list_cnt = 0;
			infop++;
		}
	}

	/*
	 * Setup the next CPU context info ptr for each MRQ.
	 * MRQ 0 will cycle thru CPUs 0 - X separately from
	 * MRQ 1 cycling thru CPUs 0 - X, and so on.
	 */
	for (j = 0; j < phba->cfg_nvmet_mrq; j++) {
		last_infop = lpfc_get_ctx_list(phba, 0, j);
		for (i = phba->sli4_hba.num_present_cpu - 1;  i >= 0; i--) {
			infop = lpfc_get_ctx_list(phba, i, j);
			infop->nvmet_ctx_next_cpu = last_infop;
			last_infop = infop;
		}
	}

	/* For all nvmet xris, allocate resources needed to process a
	 * received command on a per xri basis.
	 */
	idx = 0;
	for (i = 0; i < phba->sli4_hba.nvmet_xri_cnt; i++) {
		ctx_buf = kzalloc(sizeof(*ctx_buf), GFP_KERNEL);
		if (!ctx_buf) {
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME,
					"6404 Ran out of memory for NVMET\n");
			return -ENOMEM;
		}

		ctx_buf->context = kzalloc(sizeof(*ctx_buf->context),
					   GFP_KERNEL);
		if (!ctx_buf->context) {
			kfree(ctx_buf);
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME,
					"6405 Ran out of NVMET "
					"context memory\n");
			return -ENOMEM;
		}
		ctx_buf->context->ctxbuf = ctx_buf;
		ctx_buf->context->state = LPFC_NVMET_STE_FREE;

		ctx_buf->iocbq = lpfc_sli_get_iocbq(phba);
		if (!ctx_buf->iocbq) {
			kfree(ctx_buf->context);
			kfree(ctx_buf);
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME,
					"6406 Ran out of NVMET iocb/WQEs\n");
			return -ENOMEM;
		}
		ctx_buf->iocbq->iocb_flag = LPFC_IO_NVMET;
		nvmewqe = ctx_buf->iocbq;
		wqe = &nvmewqe->wqe;

		/* Initialize WQE */
		memset(wqe, 0, sizeof(union lpfc_wqe));

		ctx_buf->iocbq->context1 = NULL;
		spin_lock(&phba->sli4_hba.sgl_list_lock);
		ctx_buf->sglq = __lpfc_sli_get_nvmet_sglq(phba, ctx_buf->iocbq);
		spin_unlock(&phba->sli4_hba.sgl_list_lock);
		if (!ctx_buf->sglq) {
			lpfc_sli_release_iocbq(phba, ctx_buf->iocbq);
			kfree(ctx_buf->context);
			kfree(ctx_buf);
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME,
					"6407 Ran out of NVMET XRIs\n");
			return -ENOMEM;
		}

		/*
		 * Add ctx to MRQidx context list. Our initial assumption
		 * is MRQidx will be associated with CPUidx. This association
		 * can change on the fly.
		 */
		infop = lpfc_get_ctx_list(phba, idx, idx);
		spin_lock(&infop->nvmet_ctx_list_lock);
		list_add_tail(&ctx_buf->list, &infop->nvmet_ctx_list);
		infop->nvmet_ctx_list_cnt++;
		spin_unlock(&infop->nvmet_ctx_list_lock);

		/* Spread ctx structures evenly across all MRQs */
		idx++;
		if (idx >= phba->cfg_nvmet_mrq)
			idx = 0;
	}

	infop = phba->sli4_hba.nvmet_ctx_info;
	for (j = 0; j < phba->cfg_nvmet_mrq; j++) {
		for (i = 0; i < phba->sli4_hba.num_present_cpu; i++) {
			lpfc_printf_log(phba, KERN_INFO, LOG_NVME | LOG_INIT,
					"6408 TOTAL NVMET ctx for CPU %d "
					"MRQ %d: cnt %d nextcpu %p\n",
					i, j, infop->nvmet_ctx_list_cnt,
					infop->nvmet_ctx_next_cpu);
			infop++;
		}
	}
	return 0;
}