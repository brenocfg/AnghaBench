#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_4__* device; scalar_t__ host_scribble; } ;
struct lpfc_vport {int cfg_devloss_tmo; struct lpfc_hba* phba; } ;
struct lpfc_sli_ring {size_t ringno; int /*<<< orphan*/  ring_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  abortIoTag; int /*<<< orphan*/  abortContextTag; int /*<<< orphan*/  abortType; } ;
struct TYPE_10__ {TYPE_1__ acxri; } ;
struct TYPE_16__ {int ulpLe; int /*<<< orphan*/  ulpCommand; int /*<<< orphan*/  ulpClass; int /*<<< orphan*/  ulpIoTag; TYPE_2__ un; int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {int iocb_flag; size_t hba_wqidx; int /*<<< orphan*/  sli4_xritag; struct lpfc_vport* vport; int /*<<< orphan*/  iocb_cmpl; TYPE_8__ iocb; struct lpfc_scsi_buf* context1; } ;
struct lpfc_scsi_buf {struct scsi_cmnd* pCmd; int /*<<< orphan*/ * waitq; struct lpfc_iocbq cur_iocbq; } ;
struct TYPE_11__ {int /*<<< orphan*/ * sli3_ring; } ;
struct TYPE_15__ {TYPE_6__* oas_wq; TYPE_5__** fcp_wq; } ;
struct lpfc_hba {int hba_flag; scalar_t__ sli_rev; int cfg_poll; int /*<<< orphan*/  hbalock; TYPE_3__ sli; TYPE_7__ sli4_hba; int /*<<< orphan*/  cfg_fof; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; scalar_t__ hostdata; } ;
struct TYPE_14__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_13__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_12__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; struct Scsi_Host* host; } ;
typedef  TYPE_8__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_TYPE_ABTS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CMD_ABORT_XRI_CN ; 
 int /*<<< orphan*/  CMD_CLOSE_XRI_CN ; 
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int DISABLE_FCP_RING_INT ; 
 int FAILED ; 
 int /*<<< orphan*/  HA_R0RE_REQ ; 
 int HBA_FCP_IOQ_FLUSH ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int LPFC_DRIVER_ABORTED ; 
 size_t LPFC_FCP_RING ; 
 int LPFC_IO_FOF ; 
 int LPFC_IO_ON_TXCMPLQ ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int LPFC_USE_FCPWQIDX ; 
 int SUCCESS ; 
 struct lpfc_iocbq* __lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int __lpfc_sli_issue_iocb (struct lpfc_hba*,size_t,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 scalar_t__ lpfc_is_link_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_sli_abort_fcp_cmpl ; 
 int /*<<< orphan*/  lpfc_sli_handle_fast_ring_event (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq ; 

__attribute__((used)) static int
lpfc_abort_handler(struct scsi_cmnd *cmnd)
{
	struct Scsi_Host  *shost = cmnd->device->host;
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_iocbq *iocb;
	struct lpfc_iocbq *abtsiocb;
	struct lpfc_scsi_buf *lpfc_cmd;
	IOCB_t *cmd, *icmd;
	int ret = SUCCESS, status = 0;
	struct lpfc_sli_ring *pring_s4 = NULL;
	int ret_val;
	unsigned long flags;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(waitq);

	status = fc_block_scsi_eh(cmnd);
	if (status != 0 && status != SUCCESS)
		return status;

	spin_lock_irqsave(&phba->hbalock, flags);
	/* driver queued commands are in process of being flushed */
	if (phba->hba_flag & HBA_FCP_IOQ_FLUSH) {
		spin_unlock_irqrestore(&phba->hbalock, flags);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			"3168 SCSI Layer abort requested I/O has been "
			"flushed by LLD.\n");
		return FAILED;
	}

	lpfc_cmd = (struct lpfc_scsi_buf *)cmnd->host_scribble;
	if (!lpfc_cmd || !lpfc_cmd->pCmd) {
		spin_unlock_irqrestore(&phba->hbalock, flags);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			 "2873 SCSI Layer I/O Abort Request IO CMPL Status "
			 "x%x ID %d LUN %llu\n",
			 SUCCESS, cmnd->device->id, cmnd->device->lun);
		return SUCCESS;
	}

	iocb = &lpfc_cmd->cur_iocbq;
	if (phba->sli_rev == LPFC_SLI_REV4) {
		if (!(phba->cfg_fof) ||
		    (!(iocb->iocb_flag & LPFC_IO_FOF))) {
			pring_s4 =
				phba->sli4_hba.fcp_wq[iocb->hba_wqidx]->pring;
		} else {
			iocb->hba_wqidx = 0;
			pring_s4 = phba->sli4_hba.oas_wq->pring;
		}
		if (!pring_s4) {
			ret = FAILED;
			goto out_unlock;
		}
		spin_lock(&pring_s4->ring_lock);
	}
	/* the command is in process of being cancelled */
	if (!(iocb->iocb_flag & LPFC_IO_ON_TXCMPLQ)) {
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_unlock(&pring_s4->ring_lock);
		spin_unlock_irqrestore(&phba->hbalock, flags);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			"3169 SCSI Layer abort requested I/O has been "
			"cancelled by LLD.\n");
		return FAILED;
	}
	/*
	 * If pCmd field of the corresponding lpfc_scsi_buf structure
	 * points to a different SCSI command, then the driver has
	 * already completed this command, but the midlayer did not
	 * see the completion before the eh fired. Just return SUCCESS.
	 */
	if (lpfc_cmd->pCmd != cmnd) {
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_unlock(&pring_s4->ring_lock);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			"3170 SCSI Layer abort requested I/O has been "
			"completed by LLD.\n");
		goto out_unlock;
	}

	BUG_ON(iocb->context1 != lpfc_cmd);

	/* abort issued in recovery is still in progress */
	if (iocb->iocb_flag & LPFC_DRIVER_ABORTED) {
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			 "3389 SCSI Layer I/O Abort Request is pending\n");
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_unlock(&pring_s4->ring_lock);
		spin_unlock_irqrestore(&phba->hbalock, flags);
		goto wait_for_cmpl;
	}

	abtsiocb = __lpfc_sli_get_iocbq(phba);
	if (abtsiocb == NULL) {
		ret = FAILED;
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_unlock(&pring_s4->ring_lock);
		goto out_unlock;
	}

	/* Indicate the IO is being aborted by the driver. */
	iocb->iocb_flag |= LPFC_DRIVER_ABORTED;

	/*
	 * The scsi command can not be in txq and it is in flight because the
	 * pCmd is still pointig at the SCSI command we have to abort. There
	 * is no need to search the txcmplq. Just send an abort to the FW.
	 */

	cmd = &iocb->iocb;
	icmd = &abtsiocb->iocb;
	icmd->un.acxri.abortType = ABORT_TYPE_ABTS;
	icmd->un.acxri.abortContextTag = cmd->ulpContext;
	if (phba->sli_rev == LPFC_SLI_REV4)
		icmd->un.acxri.abortIoTag = iocb->sli4_xritag;
	else
		icmd->un.acxri.abortIoTag = cmd->ulpIoTag;

	icmd->ulpLe = 1;
	icmd->ulpClass = cmd->ulpClass;

	/* ABTS WQE must go to the same WQ as the WQE to be aborted */
	abtsiocb->hba_wqidx = iocb->hba_wqidx;
	abtsiocb->iocb_flag |= LPFC_USE_FCPWQIDX;
	if (iocb->iocb_flag & LPFC_IO_FOF)
		abtsiocb->iocb_flag |= LPFC_IO_FOF;

	if (lpfc_is_link_up(phba))
		icmd->ulpCommand = CMD_ABORT_XRI_CN;
	else
		icmd->ulpCommand = CMD_CLOSE_XRI_CN;

	abtsiocb->iocb_cmpl = lpfc_sli_abort_fcp_cmpl;
	abtsiocb->vport = vport;
	lpfc_cmd->waitq = &waitq;
	if (phba->sli_rev == LPFC_SLI_REV4) {
		/* Note: both hbalock and ring_lock must be set here */
		ret_val = __lpfc_sli_issue_iocb(phba, pring_s4->ringno,
						abtsiocb, 0);
		spin_unlock(&pring_s4->ring_lock);
	} else {
		ret_val = __lpfc_sli_issue_iocb(phba, LPFC_FCP_RING,
						abtsiocb, 0);
	}
	/* no longer need the lock after this point */
	spin_unlock_irqrestore(&phba->hbalock, flags);


	if (ret_val == IOCB_ERROR) {
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_lock_irqsave(&pring_s4->ring_lock, flags);
		else
			spin_lock_irqsave(&phba->hbalock, flags);
		/* Indicate the IO is not being aborted by the driver. */
		iocb->iocb_flag &= ~LPFC_DRIVER_ABORTED;
		lpfc_cmd->waitq = NULL;
		if (phba->sli_rev == LPFC_SLI_REV4)
			spin_unlock_irqrestore(&pring_s4->ring_lock, flags);
		else
			spin_unlock_irqrestore(&phba->hbalock, flags);
		lpfc_sli_release_iocbq(phba, abtsiocb);
		ret = FAILED;
		goto out;
	}

	if (phba->cfg_poll & DISABLE_FCP_RING_INT)
		lpfc_sli_handle_fast_ring_event(phba,
			&phba->sli.sli3_ring[LPFC_FCP_RING], HA_R0RE_REQ);

wait_for_cmpl:
	/* Wait for abort to complete */
	wait_event_timeout(waitq,
			  (lpfc_cmd->pCmd != cmnd),
			   msecs_to_jiffies(2*vport->cfg_devloss_tmo*1000));

	spin_lock_irqsave(shost->host_lock, flags);
	lpfc_cmd->waitq = NULL;
	spin_unlock_irqrestore(shost->host_lock, flags);

	if (lpfc_cmd->pCmd == cmnd) {
		ret = FAILED;
		lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
				 "0748 abort handler timed out waiting "
				 "for aborting I/O (xri:x%x) to complete: "
				 "ret %#x, ID %d, LUN %llu\n",
				 iocb->sli4_xritag, ret,
				 cmnd->device->id, cmnd->device->lun);
	}
	goto out;

out_unlock:
	spin_unlock_irqrestore(&phba->hbalock, flags);
out:
	lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
			 "0749 SCSI Layer I/O Abort Request Status x%x ID %d "
			 "LUN %llu\n", ret, cmnd->device->id,
			 cmnd->device->lun);
	return ret;
}