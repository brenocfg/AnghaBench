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
struct nvmefc_fcp_req {scalar_t__ io_dir; scalar_t__ sg_cnt; scalar_t__ cmdaddr; struct lpfc_nvme_fcpreq_priv* private; } ;
struct nvme_fc_remote_port {int port_id; scalar_t__ private; } ;
struct nvme_fc_local_port {scalar_t__ private; } ;
struct nvme_common_command {scalar_t__ opcode; } ;
struct TYPE_3__ {struct nvme_common_command common; } ;
struct nvme_fc_cmd_iu {TYPE_1__ sqe; } ;
struct lpfc_vport {int load_flag; int fc_myDID; struct lpfc_hba* phba; } ;
struct lpfc_nvme_rport {struct lpfc_nodelist* ndlp; } ;
struct lpfc_nvme_qhandle {int index; int /*<<< orphan*/  qidx; } ;
struct lpfc_nvme_lport {int /*<<< orphan*/  xmt_fcp_wqerr; int /*<<< orphan*/  xmt_fcp_err; struct lpfc_nvme_ctrl_stat* cstat; int /*<<< orphan*/  xmt_fcp_noxri; int /*<<< orphan*/  xmt_fcp_qdepth; int /*<<< orphan*/  xmt_fcp_bad_ndlp; struct lpfc_vport* vport; } ;
struct lpfc_nvme_fcpreq_priv {struct lpfc_nvme_buf* nvme_buf; } ;
struct lpfc_nvme_ctrl_stat {int /*<<< orphan*/  fc4NvmeControlRequests; int /*<<< orphan*/  fc4NvmeInputRequests; int /*<<< orphan*/  fc4NvmeOutputRequests; } ;
struct TYPE_4__ {int sli4_xritag; int /*<<< orphan*/  hba_wqidx; } ;
struct lpfc_nvme_buf {struct nvmefc_fcp_req* nvmeCmd; TYPE_2__ cur_iocbq; int /*<<< orphan*/  start_time; struct lpfc_nodelist* ndlp; struct lpfc_nvme_rport* nrport; } ;
struct lpfc_nodelist {int nlp_type; int nlp_state; int upcall_flags; int cmd_qdepth; int nlp_DID; int /*<<< orphan*/  cmd_pending; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_NODE ; 
 int LOG_NVME_IOERR ; 
 int /*<<< orphan*/  LPFC_FCP_RING ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int NLP_NVME_TARGET ; 
 int NLP_STE_MAPPED_NODE ; 
 scalar_t__ NVMEFC_FCP_WRITE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct lpfc_nvme_buf* lpfc_get_nvme_buf (struct lpfc_hba*,struct lpfc_nodelist*,int) ; 
 scalar_t__ lpfc_ndlp_check_qdepth (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nvme_prep_io_cmd (struct lpfc_vport*,struct lpfc_nvme_buf*,struct lpfc_nodelist*,struct lpfc_nvme_ctrl_stat*) ; 
 int lpfc_nvme_prep_io_dma (struct lpfc_vport*,struct lpfc_nvme_buf*) ; 
 int /*<<< orphan*/  lpfc_nvmeio_data (struct lpfc_hba*,char*,int,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  lpfc_release_nvme_buf (struct lpfc_hba*,struct lpfc_nvme_buf*) ; 
 int lpfc_sli4_issue_wqe (struct lpfc_hba*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ nvme_admin_keep_alive ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_nvme_fcp_io_submit(struct nvme_fc_local_port *pnvme_lport,
			struct nvme_fc_remote_port *pnvme_rport,
			void *hw_queue_handle,
			struct nvmefc_fcp_req *pnvme_fcreq)
{
	int ret = 0;
	int expedite = 0;
	int idx;
	struct lpfc_nvme_lport *lport;
	struct lpfc_nvme_ctrl_stat *cstat;
	struct lpfc_vport *vport;
	struct lpfc_hba *phba;
	struct lpfc_nodelist *ndlp;
	struct lpfc_nvme_buf *lpfc_ncmd;
	struct lpfc_nvme_rport *rport;
	struct lpfc_nvme_qhandle *lpfc_queue_info;
	struct lpfc_nvme_fcpreq_priv *freqpriv;
	struct nvme_common_command *sqe;
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	uint64_t start = 0;
#endif

	/* Validate pointers. LLDD fault handling with transport does
	 * have timing races.
	 */
	lport = (struct lpfc_nvme_lport *)pnvme_lport->private;
	if (unlikely(!lport)) {
		ret = -EINVAL;
		goto out_fail;
	}

	vport = lport->vport;

	if (unlikely(!hw_queue_handle)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6117 Fail IO, NULL hw_queue_handle\n");
		atomic_inc(&lport->xmt_fcp_err);
		ret = -EBUSY;
		goto out_fail;
	}

	phba = vport->phba;

	if (vport->load_flag & FC_UNLOADING) {
		ret = -ENODEV;
		goto out_fail;
	}

	if (vport->load_flag & FC_UNLOADING) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6124 Fail IO, Driver unload\n");
		atomic_inc(&lport->xmt_fcp_err);
		ret = -ENODEV;
		goto out_fail;
	}

	freqpriv = pnvme_fcreq->private;
	if (unlikely(!freqpriv)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6158 Fail IO, NULL request data\n");
		atomic_inc(&lport->xmt_fcp_err);
		ret = -EINVAL;
		goto out_fail;
	}

#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	if (phba->ktime_on)
		start = ktime_get_ns();
#endif
	rport = (struct lpfc_nvme_rport *)pnvme_rport->private;
	lpfc_queue_info = (struct lpfc_nvme_qhandle *)hw_queue_handle;

	/*
	 * Catch race where our node has transitioned, but the
	 * transport is still transitioning.
	 */
	ndlp = rport->ndlp;
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE | LOG_NVME_IOERR,
				 "6053 Fail IO, ndlp not ready: rport %p "
				  "ndlp %p, DID x%06x\n",
				 rport, ndlp, pnvme_rport->port_id);
		atomic_inc(&lport->xmt_fcp_err);
		ret = -EBUSY;
		goto out_fail;
	}

	/* The remote node has to be a mapped target or it's an error. */
	if ((ndlp->nlp_type & NLP_NVME_TARGET) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE | LOG_NVME_IOERR,
				 "6036 Fail IO, DID x%06x not ready for "
				 "IO. State x%x, Type x%x Flg x%x\n",
				 pnvme_rport->port_id,
				 ndlp->nlp_state, ndlp->nlp_type,
				 ndlp->upcall_flags);
		atomic_inc(&lport->xmt_fcp_bad_ndlp);
		ret = -EBUSY;
		goto out_fail;

	}

	/* Currently only NVME Keep alive commands should be expedited
	 * if the driver runs out of a resource. These should only be
	 * issued on the admin queue, qidx 0
	 */
	if (!lpfc_queue_info->qidx && !pnvme_fcreq->sg_cnt) {
		sqe = &((struct nvme_fc_cmd_iu *)
			pnvme_fcreq->cmdaddr)->sqe.common;
		if (sqe->opcode == nvme_admin_keep_alive)
			expedite = 1;
	}

	/* The node is shared with FCP IO, make sure the IO pending count does
	 * not exceed the programmed depth.
	 */
	if (lpfc_ndlp_check_qdepth(phba, ndlp)) {
		if ((atomic_read(&ndlp->cmd_pending) >= ndlp->cmd_qdepth) &&
		    !expedite) {
			lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
					 "6174 Fail IO, ndlp qdepth exceeded: "
					 "idx %d DID %x pend %d qdepth %d\n",
					 lpfc_queue_info->index, ndlp->nlp_DID,
					 atomic_read(&ndlp->cmd_pending),
					 ndlp->cmd_qdepth);
			atomic_inc(&lport->xmt_fcp_qdepth);
			ret = -EBUSY;
			goto out_fail;
		}
	}

	lpfc_ncmd = lpfc_get_nvme_buf(phba, ndlp, expedite);
	if (lpfc_ncmd == NULL) {
		atomic_inc(&lport->xmt_fcp_noxri);
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6065 Fail IO, driver buffer pool is empty: "
				 "idx %d DID %x\n",
				 lpfc_queue_info->index, ndlp->nlp_DID);
		ret = -EBUSY;
		goto out_fail;
	}
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	if (start) {
		lpfc_ncmd->ts_cmd_start = start;
		lpfc_ncmd->ts_last_cmd = phba->ktime_last_cmd;
	} else {
		lpfc_ncmd->ts_cmd_start = 0;
	}
#endif

	/*
	 * Store the data needed by the driver to issue, abort, and complete
	 * an IO.
	 * Do not let the IO hang out forever.  There is no midlayer issuing
	 * an abort so inform the FW of the maximum IO pending time.
	 */
	freqpriv->nvme_buf = lpfc_ncmd;
	lpfc_ncmd->nvmeCmd = pnvme_fcreq;
	lpfc_ncmd->nrport = rport;
	lpfc_ncmd->ndlp = ndlp;
	lpfc_ncmd->start_time = jiffies;

	/*
	 * Issue the IO on the WQ indicated by index in the hw_queue_handle.
	 * This identfier was create in our hardware queue create callback
	 * routine. The driver now is dependent on the IO queue steering from
	 * the transport.  We are trusting the upper NVME layers know which
	 * index to use and that they have affinitized a CPU to this hardware
	 * queue. A hardware queue maps to a driver MSI-X vector/EQ/CQ/WQ.
	 */
	idx = lpfc_queue_info->index;
	lpfc_ncmd->cur_iocbq.hba_wqidx = idx;
	cstat = &lport->cstat[idx];

	lpfc_nvme_prep_io_cmd(vport, lpfc_ncmd, ndlp, cstat);
	ret = lpfc_nvme_prep_io_dma(vport, lpfc_ncmd);
	if (ret) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6175 Fail IO, Prep DMA: "
				 "idx %d DID %x\n",
				 lpfc_queue_info->index, ndlp->nlp_DID);
		atomic_inc(&lport->xmt_fcp_err);
		ret = -ENOMEM;
		goto out_free_nvme_buf;
	}

	lpfc_nvmeio_data(phba, "NVME FCP XMIT: xri x%x idx %d to %06x\n",
			 lpfc_ncmd->cur_iocbq.sli4_xritag,
			 lpfc_queue_info->index, ndlp->nlp_DID);

	ret = lpfc_sli4_issue_wqe(phba, LPFC_FCP_RING, &lpfc_ncmd->cur_iocbq);
	if (ret) {
		atomic_inc(&lport->xmt_fcp_wqerr);
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_IOERR,
				 "6113 Fail IO, Could not issue WQE err %x "
				 "sid: x%x did: x%x oxid: x%x\n",
				 ret, vport->fc_myDID, ndlp->nlp_DID,
				 lpfc_ncmd->cur_iocbq.sli4_xritag);
		goto out_free_nvme_buf;
	}

#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	if (lpfc_ncmd->ts_cmd_start)
		lpfc_ncmd->ts_cmd_wqput = ktime_get_ns();

	if (phba->cpucheck_on & LPFC_CHECK_NVME_IO) {
		lpfc_ncmd->cpu = smp_processor_id();
		if (lpfc_ncmd->cpu != lpfc_queue_info->index) {
			/* Check for admin queue */
			if (lpfc_queue_info->qidx) {
				lpfc_printf_vlog(vport,
						 KERN_ERR, LOG_NVME_IOERR,
						"6702 CPU Check cmd: "
						"cpu %d wq %d\n",
						lpfc_ncmd->cpu,
						lpfc_queue_info->index);
			}
			lpfc_ncmd->cpu = lpfc_queue_info->index;
		}
		if (lpfc_ncmd->cpu < LPFC_CHECK_CPU_CNT)
			phba->cpucheck_xmt_io[lpfc_ncmd->cpu]++;
	}
#endif
	return 0;

 out_free_nvme_buf:
	if (lpfc_ncmd->nvmeCmd->sg_cnt) {
		if (lpfc_ncmd->nvmeCmd->io_dir == NVMEFC_FCP_WRITE)
			atomic_dec(&cstat->fc4NvmeOutputRequests);
		else
			atomic_dec(&cstat->fc4NvmeInputRequests);
	} else
		atomic_dec(&cstat->fc4NvmeControlRequests);
	lpfc_release_nvme_buf(phba, lpfc_ncmd);
 out_fail:
	return ret;
}