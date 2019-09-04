#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_22__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;

/* Type definitions */
union lpfc_sli4_cfg_shdr {int /*<<< orphan*/  response; } ;
typedef  int uint32_t ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct lpfc_mbx_query_fw_config {int dummy; } ;
struct TYPE_39__ {TYPE_15__* els_cq; TYPE_14__* dat_rq; TYPE_13__* hdr_rq; TYPE_15__** nvmet_cqset; TYPE_14__** nvmet_mrq_data; TYPE_13__** nvmet_mrq_hdr; TYPE_15__* nvmels_cq; TYPE_22__* nvmels_wq; TYPE_19__** hba_eq; TYPE_22__* els_wq; TYPE_22__* mbx_wq; TYPE_15__* mbx_cq; int /*<<< orphan*/ * fcp_cq_map; TYPE_22__** fcp_wq; TYPE_15__** fcp_cq; int /*<<< orphan*/ * nvme_cq_map; TYPE_22__** nvme_wq; TYPE_15__** nvme_cq; int /*<<< orphan*/  ulp1_mode; int /*<<< orphan*/  ulp0_mode; int /*<<< orphan*/  fw_func_mode; int /*<<< orphan*/  physical_port; } ;
struct lpfc_hba {int io_channel_irqs; int cfg_nvme_io_channel; int cfg_fcp_io_channel; int cfg_nvmet_mrq; int /*<<< orphan*/  cfg_fcp_imax; scalar_t__ cfg_fof; TYPE_8__ sli4_hba; scalar_t__ nvmet_support; int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_34__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  ulp1_mode; int /*<<< orphan*/  ulp0_mode; int /*<<< orphan*/  function_mode; } ;
struct TYPE_35__ {TYPE_3__ rsp; } ;
struct TYPE_31__ {int /*<<< orphan*/  cfg_shdr; } ;
struct TYPE_33__ {TYPE_1__ header; } ;
struct TYPE_36__ {TYPE_4__ query_fw_cfg; TYPE_2__ sli4_config; } ;
struct TYPE_37__ {TYPE_5__ un; } ;
struct TYPE_38__ {TYPE_6__ mqe; } ;
struct TYPE_40__ {TYPE_7__ u; } ;
struct TYPE_32__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_30__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_29__ {int /*<<< orphan*/  queue_id; scalar_t__ chann; } ;
struct TYPE_28__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_27__ {int /*<<< orphan*/  queue_id; } ;
typedef  TYPE_9__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_ELS ; 
 int /*<<< orphan*/  LPFC_FCP ; 
 scalar_t__ LPFC_MAX_EQ_DELAY_EQID_CNT ; 
 int /*<<< orphan*/  LPFC_MBOX ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_QUERY_FW_CFG ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  LPFC_NVME ; 
 int /*<<< orphan*/  LPFC_NVMET ; 
 int /*<<< orphan*/  LPFC_NVME_LS ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int /*<<< orphan*/  LPFC_USOL ; 
 int /*<<< orphan*/  LPFC_WCQ ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_TIMEOUT ; 
 int bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lpfc_cq_create (struct lpfc_hba*,TYPE_15__*,TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_cq_create_set (struct lpfc_hba*,TYPE_15__**,TYPE_19__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_create_wq_cq (struct lpfc_hba*,TYPE_19__*,TYPE_15__*,TYPE_22__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lpfc_eq_create (struct lpfc_hba*,TYPE_19__*,int /*<<< orphan*/ ) ; 
 int lpfc_fof_queue_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_add_status ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_status ; 
 int /*<<< orphan*/  lpfc_modify_hba_eq_delay (struct lpfc_hba*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int lpfc_mrq_create (struct lpfc_hba*,TYPE_13__**,TYPE_14__**,TYPE_15__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int lpfc_rq_create (struct lpfc_hba*,TYPE_13__*,TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_config (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_queue_unset (struct lpfc_hba*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_9__*,int /*<<< orphan*/ ) ; 

int
lpfc_sli4_queue_setup(struct lpfc_hba *phba)
{
	uint32_t shdr_status, shdr_add_status;
	union lpfc_sli4_cfg_shdr *shdr;
	LPFC_MBOXQ_t *mboxq;
	int qidx;
	uint32_t length, io_channel;
	int rc = -ENOMEM;

	/* Check for dual-ULP support */
	mboxq = (LPFC_MBOXQ_t *)mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mboxq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3249 Unable to allocate memory for "
				"QUERY_FW_CFG mailbox command\n");
		return -ENOMEM;
	}
	length = (sizeof(struct lpfc_mbx_query_fw_config) -
		  sizeof(struct lpfc_sli4_cfg_mhdr));
	lpfc_sli4_config(phba, mboxq, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_QUERY_FW_CFG,
			 length, LPFC_SLI4_MBX_EMBED);

	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);

	shdr = (union lpfc_sli4_cfg_shdr *)
			&mboxq->u.mqe.un.sli4_config.header.cfg_shdr;
	shdr_status = bf_get(lpfc_mbox_hdr_status, &shdr->response);
	shdr_add_status = bf_get(lpfc_mbox_hdr_add_status, &shdr->response);
	if (shdr_status || shdr_add_status || rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3250 QUERY_FW_CFG mailbox failed with status "
				"x%x add_status x%x, mbx status x%x\n",
				shdr_status, shdr_add_status, rc);
		if (rc != MBX_TIMEOUT)
			mempool_free(mboxq, phba->mbox_mem_pool);
		rc = -ENXIO;
		goto out_error;
	}

	phba->sli4_hba.fw_func_mode =
			mboxq->u.mqe.un.query_fw_cfg.rsp.function_mode;
	phba->sli4_hba.ulp0_mode = mboxq->u.mqe.un.query_fw_cfg.rsp.ulp0_mode;
	phba->sli4_hba.ulp1_mode = mboxq->u.mqe.un.query_fw_cfg.rsp.ulp1_mode;
	phba->sli4_hba.physical_port =
			mboxq->u.mqe.un.query_fw_cfg.rsp.physical_port;
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"3251 QUERY_FW_CFG: func_mode:x%x, ulp0_mode:x%x, "
			"ulp1_mode:x%x\n", phba->sli4_hba.fw_func_mode,
			phba->sli4_hba.ulp0_mode, phba->sli4_hba.ulp1_mode);

	if (rc != MBX_TIMEOUT)
		mempool_free(mboxq, phba->mbox_mem_pool);

	/*
	 * Set up HBA Event Queues (EQs)
	 */
	io_channel = phba->io_channel_irqs;

	/* Set up HBA event queue */
	if (io_channel && !phba->sli4_hba.hba_eq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3147 Fast-path EQs not allocated\n");
		rc = -ENOMEM;
		goto out_error;
	}
	for (qidx = 0; qidx < io_channel; qidx++) {
		if (!phba->sli4_hba.hba_eq[qidx]) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0522 Fast-path EQ (%d) not "
					"allocated\n", qidx);
			rc = -ENOMEM;
			goto out_destroy;
		}
		rc = lpfc_eq_create(phba, phba->sli4_hba.hba_eq[qidx],
						phba->cfg_fcp_imax);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0523 Failed setup of fast-path EQ "
					"(%d), rc = 0x%x\n", qidx,
					(uint32_t)rc);
			goto out_destroy;
		}
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"2584 HBA EQ setup: queue[%d]-id=%d\n",
				qidx, phba->sli4_hba.hba_eq[qidx]->queue_id);
	}

	if (phba->cfg_nvme_io_channel) {
		if (!phba->sli4_hba.nvme_cq || !phba->sli4_hba.nvme_wq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"6084 Fast-path NVME %s array not allocated\n",
				(phba->sli4_hba.nvme_cq) ? "CQ" : "WQ");
			rc = -ENOMEM;
			goto out_destroy;
		}

		for (qidx = 0; qidx < phba->cfg_nvme_io_channel; qidx++) {
			rc = lpfc_create_wq_cq(phba,
					phba->sli4_hba.hba_eq[
						qidx % io_channel],
					phba->sli4_hba.nvme_cq[qidx],
					phba->sli4_hba.nvme_wq[qidx],
					&phba->sli4_hba.nvme_cq_map[qidx],
					qidx, LPFC_NVME);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6123 Failed to setup fastpath "
					"NVME WQ/CQ (%d), rc = 0x%x\n",
					qidx, (uint32_t)rc);
				goto out_destroy;
			}
		}
	}

	if (phba->cfg_fcp_io_channel) {
		/* Set up fast-path FCP Response Complete Queue */
		if (!phba->sli4_hba.fcp_cq || !phba->sli4_hba.fcp_wq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3148 Fast-path FCP %s array not allocated\n",
				phba->sli4_hba.fcp_cq ? "WQ" : "CQ");
			rc = -ENOMEM;
			goto out_destroy;
		}

		for (qidx = 0; qidx < phba->cfg_fcp_io_channel; qidx++) {
			rc = lpfc_create_wq_cq(phba,
					phba->sli4_hba.hba_eq[
						qidx % io_channel],
					phba->sli4_hba.fcp_cq[qidx],
					phba->sli4_hba.fcp_wq[qidx],
					&phba->sli4_hba.fcp_cq_map[qidx],
					qidx, LPFC_FCP);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0535 Failed to setup fastpath "
					"FCP WQ/CQ (%d), rc = 0x%x\n",
					qidx, (uint32_t)rc);
				goto out_destroy;
			}
		}
	}

	/*
	 * Set up Slow Path Complete Queues (CQs)
	 */

	/* Set up slow-path MBOX CQ/MQ */

	if (!phba->sli4_hba.mbx_cq || !phba->sli4_hba.mbx_wq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0528 %s not allocated\n",
				phba->sli4_hba.mbx_cq ?
				"Mailbox WQ" : "Mailbox CQ");
		rc = -ENOMEM;
		goto out_destroy;
	}

	rc = lpfc_create_wq_cq(phba, phba->sli4_hba.hba_eq[0],
			       phba->sli4_hba.mbx_cq,
			       phba->sli4_hba.mbx_wq,
			       NULL, 0, LPFC_MBOX);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"0529 Failed setup of mailbox WQ/CQ: rc = 0x%x\n",
			(uint32_t)rc);
		goto out_destroy;
	}
	if (phba->nvmet_support) {
		if (!phba->sli4_hba.nvmet_cqset) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3165 Fast-path NVME CQ Set "
					"array not allocated\n");
			rc = -ENOMEM;
			goto out_destroy;
		}
		if (phba->cfg_nvmet_mrq > 1) {
			rc = lpfc_cq_create_set(phba,
					phba->sli4_hba.nvmet_cqset,
					phba->sli4_hba.hba_eq,
					LPFC_WCQ, LPFC_NVMET);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"3164 Failed setup of NVME CQ "
						"Set, rc = 0x%x\n",
						(uint32_t)rc);
				goto out_destroy;
			}
		} else {
			/* Set up NVMET Receive Complete Queue */
			rc = lpfc_cq_create(phba, phba->sli4_hba.nvmet_cqset[0],
					    phba->sli4_hba.hba_eq[0],
					    LPFC_WCQ, LPFC_NVMET);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6089 Failed setup NVMET CQ: "
						"rc = 0x%x\n", (uint32_t)rc);
				goto out_destroy;
			}
			phba->sli4_hba.nvmet_cqset[0]->chann = 0;

			lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
					"6090 NVMET CQ setup: cq-id=%d, "
					"parent eq-id=%d\n",
					phba->sli4_hba.nvmet_cqset[0]->queue_id,
					phba->sli4_hba.hba_eq[0]->queue_id);
		}
	}

	/* Set up slow-path ELS WQ/CQ */
	if (!phba->sli4_hba.els_cq || !phba->sli4_hba.els_wq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0530 ELS %s not allocated\n",
				phba->sli4_hba.els_cq ? "WQ" : "CQ");
		rc = -ENOMEM;
		goto out_destroy;
	}
	rc = lpfc_create_wq_cq(phba, phba->sli4_hba.hba_eq[0],
					phba->sli4_hba.els_cq,
					phba->sli4_hba.els_wq,
					NULL, 0, LPFC_ELS);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"0529 Failed setup of ELS WQ/CQ: rc = 0x%x\n",
			(uint32_t)rc);
		goto out_destroy;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2590 ELS WQ setup: wq-id=%d, parent cq-id=%d\n",
			phba->sli4_hba.els_wq->queue_id,
			phba->sli4_hba.els_cq->queue_id);

	if (phba->cfg_nvme_io_channel) {
		/* Set up NVME LS Complete Queue */
		if (!phba->sli4_hba.nvmels_cq || !phba->sli4_hba.nvmels_wq) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6091 LS %s not allocated\n",
					phba->sli4_hba.nvmels_cq ? "WQ" : "CQ");
			rc = -ENOMEM;
			goto out_destroy;
		}
		rc = lpfc_create_wq_cq(phba, phba->sli4_hba.hba_eq[0],
					phba->sli4_hba.nvmels_cq,
					phba->sli4_hba.nvmels_wq,
					NULL, 0, LPFC_NVME_LS);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0529 Failed setup of NVVME LS WQ/CQ: "
				"rc = 0x%x\n", (uint32_t)rc);
			goto out_destroy;
		}

		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"6096 ELS WQ setup: wq-id=%d, "
				"parent cq-id=%d\n",
				phba->sli4_hba.nvmels_wq->queue_id,
				phba->sli4_hba.nvmels_cq->queue_id);
	}

	/*
	 * Create NVMET Receive Queue (RQ)
	 */
	if (phba->nvmet_support) {
		if ((!phba->sli4_hba.nvmet_cqset) ||
		    (!phba->sli4_hba.nvmet_mrq_hdr) ||
		    (!phba->sli4_hba.nvmet_mrq_data)) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6130 MRQ CQ Queues not "
					"allocated\n");
			rc = -ENOMEM;
			goto out_destroy;
		}
		if (phba->cfg_nvmet_mrq > 1) {
			rc = lpfc_mrq_create(phba,
					     phba->sli4_hba.nvmet_mrq_hdr,
					     phba->sli4_hba.nvmet_mrq_data,
					     phba->sli4_hba.nvmet_cqset,
					     LPFC_NVMET);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6098 Failed setup of NVMET "
						"MRQ: rc = 0x%x\n",
						(uint32_t)rc);
				goto out_destroy;
			}

		} else {
			rc = lpfc_rq_create(phba,
					    phba->sli4_hba.nvmet_mrq_hdr[0],
					    phba->sli4_hba.nvmet_mrq_data[0],
					    phba->sli4_hba.nvmet_cqset[0],
					    LPFC_NVMET);
			if (rc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6057 Failed setup of NVMET "
						"Receive Queue: rc = 0x%x\n",
						(uint32_t)rc);
				goto out_destroy;
			}

			lpfc_printf_log(
				phba, KERN_INFO, LOG_INIT,
				"6099 NVMET RQ setup: hdr-rq-id=%d, "
				"dat-rq-id=%d parent cq-id=%d\n",
				phba->sli4_hba.nvmet_mrq_hdr[0]->queue_id,
				phba->sli4_hba.nvmet_mrq_data[0]->queue_id,
				phba->sli4_hba.nvmet_cqset[0]->queue_id);

		}
	}

	if (!phba->sli4_hba.hdr_rq || !phba->sli4_hba.dat_rq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0540 Receive Queue not allocated\n");
		rc = -ENOMEM;
		goto out_destroy;
	}

	rc = lpfc_rq_create(phba, phba->sli4_hba.hdr_rq, phba->sli4_hba.dat_rq,
			    phba->sli4_hba.els_cq, LPFC_USOL);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0541 Failed setup of Receive Queue: "
				"rc = 0x%x\n", (uint32_t)rc);
		goto out_destroy;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2592 USL RQ setup: hdr-rq-id=%d, dat-rq-id=%d "
			"parent cq-id=%d\n",
			phba->sli4_hba.hdr_rq->queue_id,
			phba->sli4_hba.dat_rq->queue_id,
			phba->sli4_hba.els_cq->queue_id);

	if (phba->cfg_fof) {
		rc = lpfc_fof_queue_setup(phba);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0549 Failed setup of FOF Queues: "
					"rc = 0x%x\n", rc);
			goto out_destroy;
		}
	}

	for (qidx = 0; qidx < io_channel; qidx += LPFC_MAX_EQ_DELAY_EQID_CNT)
		lpfc_modify_hba_eq_delay(phba, qidx, LPFC_MAX_EQ_DELAY_EQID_CNT,
					 phba->cfg_fcp_imax);

	return 0;

out_destroy:
	lpfc_sli4_queue_unset(phba);
out_error:
	return rc;
}