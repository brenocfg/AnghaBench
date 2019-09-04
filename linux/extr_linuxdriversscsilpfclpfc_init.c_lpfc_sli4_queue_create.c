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
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_rqb {int dummy; } ;
struct lpfc_queue {int qe_valid; TYPE_2__* rqbp; int /*<<< orphan*/  wq_list; } ;
struct TYPE_3__ {struct lpfc_queue** nvmet_mrq_data; int /*<<< orphan*/  rq_esize; struct lpfc_queue** nvmet_mrq_hdr; struct lpfc_queue* dat_rq; int /*<<< orphan*/  rq_ecount; struct lpfc_queue* hdr_rq; int /*<<< orphan*/  lpfc_wq_list; struct lpfc_queue* nvmels_wq; int /*<<< orphan*/  wq_ecount; int /*<<< orphan*/  wq_esize; struct lpfc_queue* nvmels_cq; int /*<<< orphan*/  cq_ecount; int /*<<< orphan*/  cq_esize; struct lpfc_queue* els_wq; struct lpfc_queue* mbx_wq; int /*<<< orphan*/  mq_ecount; int /*<<< orphan*/  mq_esize; struct lpfc_queue* els_cq; struct lpfc_queue* mbx_cq; struct lpfc_queue** nvmet_cqset; struct lpfc_queue** hba_eq; int /*<<< orphan*/  eq_ecount; int /*<<< orphan*/  eq_esize; void* nvme_cq_map; void* nvme_wq; void* nvme_cq; void* fcp_cq_map; void* fcp_wq; void* fcp_cq; } ;
struct lpfc_hba {int io_channel_irqs; int cfg_fcp_io_channel; int cfg_nvme_io_channel; int cfg_nvmet_mrq; int cfg_enable_fc4_type; scalar_t__ cfg_fof; TYPE_1__ sli4_hba; scalar_t__ nvmet_support; } ;
struct TYPE_4__ {int /*<<< orphan*/  rqb_buffer_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_CQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_CQE_SIZE ; 
 int /*<<< orphan*/  LPFC_DEFAULT_PAGE_SIZE ; 
 int LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  LPFC_EQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_EQE_SIZE_4B ; 
 int /*<<< orphan*/  LPFC_MQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_MQE_SIZE ; 
 int /*<<< orphan*/  LPFC_NVMET_RQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_RQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_RQE_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_WQE_SIZE ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_alloc_fcp_wq_cq (struct lpfc_hba*,int) ; 
 scalar_t__ lpfc_alloc_nvme_wq_cq (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_fof_queue_create (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct lpfc_queue* lpfc_sli4_queue_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_queue_destroy (struct lpfc_hba*) ; 

int
lpfc_sli4_queue_create(struct lpfc_hba *phba)
{
	struct lpfc_queue *qdesc;
	int idx, io_channel;

	/*
	 * Create HBA Record arrays.
	 * Both NVME and FCP will share that same vectors / EQs
	 */
	io_channel = phba->io_channel_irqs;
	if (!io_channel)
		return -ERANGE;

	phba->sli4_hba.mq_esize = LPFC_MQE_SIZE;
	phba->sli4_hba.mq_ecount = LPFC_MQE_DEF_COUNT;
	phba->sli4_hba.wq_esize = LPFC_WQE_SIZE;
	phba->sli4_hba.wq_ecount = LPFC_WQE_DEF_COUNT;
	phba->sli4_hba.rq_esize = LPFC_RQE_SIZE;
	phba->sli4_hba.rq_ecount = LPFC_RQE_DEF_COUNT;
	phba->sli4_hba.eq_esize = LPFC_EQE_SIZE_4B;
	phba->sli4_hba.eq_ecount = LPFC_EQE_DEF_COUNT;
	phba->sli4_hba.cq_esize = LPFC_CQE_SIZE;
	phba->sli4_hba.cq_ecount = LPFC_CQE_DEF_COUNT;

	phba->sli4_hba.hba_eq =  kcalloc(io_channel,
					sizeof(struct lpfc_queue *),
					GFP_KERNEL);
	if (!phba->sli4_hba.hba_eq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2576 Failed allocate memory for "
			"fast-path EQ record array\n");
		goto out_error;
	}

	if (phba->cfg_fcp_io_channel) {
		phba->sli4_hba.fcp_cq = kcalloc(phba->cfg_fcp_io_channel,
						sizeof(struct lpfc_queue *),
						GFP_KERNEL);
		if (!phba->sli4_hba.fcp_cq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2577 Failed allocate memory for "
					"fast-path CQ record array\n");
			goto out_error;
		}
		phba->sli4_hba.fcp_wq = kcalloc(phba->cfg_fcp_io_channel,
						sizeof(struct lpfc_queue *),
						GFP_KERNEL);
		if (!phba->sli4_hba.fcp_wq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2578 Failed allocate memory for "
					"fast-path FCP WQ record array\n");
			goto out_error;
		}
		/*
		 * Since the first EQ can have multiple CQs associated with it,
		 * this array is used to quickly see if we have a FCP fast-path
		 * CQ match.
		 */
		phba->sli4_hba.fcp_cq_map = kcalloc(phba->cfg_fcp_io_channel,
							sizeof(uint16_t),
							GFP_KERNEL);
		if (!phba->sli4_hba.fcp_cq_map) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2545 Failed allocate memory for "
					"fast-path CQ map\n");
			goto out_error;
		}
	}

	if (phba->cfg_nvme_io_channel) {
		phba->sli4_hba.nvme_cq = kcalloc(phba->cfg_nvme_io_channel,
						sizeof(struct lpfc_queue *),
						GFP_KERNEL);
		if (!phba->sli4_hba.nvme_cq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6077 Failed allocate memory for "
					"fast-path CQ record array\n");
			goto out_error;
		}

		phba->sli4_hba.nvme_wq = kcalloc(phba->cfg_nvme_io_channel,
						sizeof(struct lpfc_queue *),
						GFP_KERNEL);
		if (!phba->sli4_hba.nvme_wq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2581 Failed allocate memory for "
					"fast-path NVME WQ record array\n");
			goto out_error;
		}

		/*
		 * Since the first EQ can have multiple CQs associated with it,
		 * this array is used to quickly see if we have a NVME fast-path
		 * CQ match.
		 */
		phba->sli4_hba.nvme_cq_map = kcalloc(phba->cfg_nvme_io_channel,
							sizeof(uint16_t),
							GFP_KERNEL);
		if (!phba->sli4_hba.nvme_cq_map) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6078 Failed allocate memory for "
					"fast-path CQ map\n");
			goto out_error;
		}

		if (phba->nvmet_support) {
			phba->sli4_hba.nvmet_cqset = kcalloc(
					phba->cfg_nvmet_mrq,
					sizeof(struct lpfc_queue *),
					GFP_KERNEL);
			if (!phba->sli4_hba.nvmet_cqset) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3121 Fail allocate memory for "
					"fast-path CQ set array\n");
				goto out_error;
			}
			phba->sli4_hba.nvmet_mrq_hdr = kcalloc(
					phba->cfg_nvmet_mrq,
					sizeof(struct lpfc_queue *),
					GFP_KERNEL);
			if (!phba->sli4_hba.nvmet_mrq_hdr) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3122 Fail allocate memory for "
					"fast-path RQ set hdr array\n");
				goto out_error;
			}
			phba->sli4_hba.nvmet_mrq_data = kcalloc(
					phba->cfg_nvmet_mrq,
					sizeof(struct lpfc_queue *),
					GFP_KERNEL);
			if (!phba->sli4_hba.nvmet_mrq_data) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3124 Fail allocate memory for "
					"fast-path RQ set data array\n");
				goto out_error;
			}
		}
	}

	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_wq_list);

	/* Create HBA Event Queues (EQs) */
	for (idx = 0; idx < io_channel; idx++) {
		/* Create EQs */
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
					      phba->sli4_hba.eq_esize,
					      phba->sli4_hba.eq_ecount);
		if (!qdesc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0497 Failed allocate EQ (%d)\n", idx);
			goto out_error;
		}
		qdesc->qe_valid = 1;
		phba->sli4_hba.hba_eq[idx] = qdesc;
	}

	/* FCP and NVME io channels are not required to be balanced */

	for (idx = 0; idx < phba->cfg_fcp_io_channel; idx++)
		if (lpfc_alloc_fcp_wq_cq(phba, idx))
			goto out_error;

	for (idx = 0; idx < phba->cfg_nvme_io_channel; idx++)
		if (lpfc_alloc_nvme_wq_cq(phba, idx))
			goto out_error;

	if (phba->nvmet_support) {
		for (idx = 0; idx < phba->cfg_nvmet_mrq; idx++) {
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_DEFAULT_PAGE_SIZE,
						      phba->sli4_hba.cq_esize,
						      phba->sli4_hba.cq_ecount);
			if (!qdesc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3142 Failed allocate NVME "
					"CQ Set (%d)\n", idx);
				goto out_error;
			}
			qdesc->qe_valid = 1;
			phba->sli4_hba.nvmet_cqset[idx] = qdesc;
		}
	}

	/*
	 * Create Slow Path Completion Queues (CQs)
	 */

	/* Create slow-path Mailbox Command Complete Queue */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.cq_esize,
				      phba->sli4_hba.cq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0500 Failed allocate slow-path mailbox CQ\n");
		goto out_error;
	}
	qdesc->qe_valid = 1;
	phba->sli4_hba.mbx_cq = qdesc;

	/* Create slow-path ELS Complete Queue */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.cq_esize,
				      phba->sli4_hba.cq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0501 Failed allocate slow-path ELS CQ\n");
		goto out_error;
	}
	qdesc->qe_valid = 1;
	phba->sli4_hba.els_cq = qdesc;


	/*
	 * Create Slow Path Work Queues (WQs)
	 */

	/* Create Mailbox Command Queue */

	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.mq_esize,
				      phba->sli4_hba.mq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0505 Failed allocate slow-path MQ\n");
		goto out_error;
	}
	phba->sli4_hba.mbx_wq = qdesc;

	/*
	 * Create ELS Work Queues
	 */

	/* Create slow-path ELS Work Queue */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.wq_esize,
				      phba->sli4_hba.wq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0504 Failed allocate slow-path ELS WQ\n");
		goto out_error;
	}
	phba->sli4_hba.els_wq = qdesc;
	list_add_tail(&qdesc->wq_list, &phba->sli4_hba.lpfc_wq_list);

	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
		/* Create NVME LS Complete Queue */
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
					      phba->sli4_hba.cq_esize,
					      phba->sli4_hba.cq_ecount);
		if (!qdesc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6079 Failed allocate NVME LS CQ\n");
			goto out_error;
		}
		qdesc->qe_valid = 1;
		phba->sli4_hba.nvmels_cq = qdesc;

		/* Create NVME LS Work Queue */
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
					      phba->sli4_hba.wq_esize,
					      phba->sli4_hba.wq_ecount);
		if (!qdesc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6080 Failed allocate NVME LS WQ\n");
			goto out_error;
		}
		phba->sli4_hba.nvmels_wq = qdesc;
		list_add_tail(&qdesc->wq_list, &phba->sli4_hba.lpfc_wq_list);
	}

	/*
	 * Create Receive Queue (RQ)
	 */

	/* Create Receive Queue for header */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.rq_esize,
				      phba->sli4_hba.rq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0506 Failed allocate receive HRQ\n");
		goto out_error;
	}
	phba->sli4_hba.hdr_rq = qdesc;

	/* Create Receive Queue for data */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.rq_esize,
				      phba->sli4_hba.rq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0507 Failed allocate receive DRQ\n");
		goto out_error;
	}
	phba->sli4_hba.dat_rq = qdesc;

	if (phba->nvmet_support) {
		for (idx = 0; idx < phba->cfg_nvmet_mrq; idx++) {
			/* Create NVMET Receive Queue for header */
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_DEFAULT_PAGE_SIZE,
						      phba->sli4_hba.rq_esize,
						      LPFC_NVMET_RQE_DEF_COUNT);
			if (!qdesc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"3146 Failed allocate "
						"receive HRQ\n");
				goto out_error;
			}
			phba->sli4_hba.nvmet_mrq_hdr[idx] = qdesc;

			/* Only needed for header of RQ pair */
			qdesc->rqbp = kzalloc(sizeof(struct lpfc_rqb),
					      GFP_KERNEL);
			if (qdesc->rqbp == NULL) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6131 Failed allocate "
						"Header RQBP\n");
				goto out_error;
			}

			/* Put list in known state in case driver load fails. */
			INIT_LIST_HEAD(&qdesc->rqbp->rqb_buffer_list);

			/* Create NVMET Receive Queue for data */
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_DEFAULT_PAGE_SIZE,
						      phba->sli4_hba.rq_esize,
						      LPFC_NVMET_RQE_DEF_COUNT);
			if (!qdesc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"3156 Failed allocate "
						"receive DRQ\n");
				goto out_error;
			}
			phba->sli4_hba.nvmet_mrq_data[idx] = qdesc;
		}
	}

	/* Create the Queues needed for Flash Optimized Fabric operations */
	if (phba->cfg_fof)
		lpfc_fof_queue_create(phba);
	return 0;

out_error:
	lpfc_sli4_queue_destroy(phba);
	return -ENOMEM;
}