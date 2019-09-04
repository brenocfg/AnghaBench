#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct lpfc_hba {scalar_t__ link_state; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  link_flag; } ;
struct TYPE_11__ {scalar_t__ vendor_cmd; } ;
struct TYPE_12__ {TYPE_1__ h_vendor; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct fc_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; } ;
struct diag_mode_set {scalar_t__ type; int timeout; } ;
struct bsg_job {int request_len; struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;
struct TYPE_13__ {int /*<<< orphan*/  link_flags; } ;
struct TYPE_14__ {TYPE_3__ varInitLnk; } ;
struct TYPE_15__ {scalar_t__ mbxStatus; void* mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_4__ un; } ;
struct TYPE_16__ {TYPE_5__ mb; } ;
struct TYPE_17__ {TYPE_6__ u; } ;
typedef  TYPE_7__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FLAGS_LOCAL_LB ; 
 int /*<<< orphan*/  FLAGS_TOPOLOGY_MODE_LOOP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INTERNAL_LOOP_BACK ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 scalar_t__ LPFC_HBA_READY ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_MBOX_TMO ; 
 int /*<<< orphan*/  LS_LOOPBACK_MODE ; 
 int /*<<< orphan*/  MBX_DOWN_LINK ; 
 int /*<<< orphan*/  MBX_INIT_LINK ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 void* OWN_HOST ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 int lpfc_bsg_diag_mode_enter (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_bsg_diag_mode_exit (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_sli3_bsg_diag_loopback_mode(struct lpfc_hba *phba, struct bsg_job *job)
{
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	struct diag_mode_set *loopback_mode;
	uint32_t link_flags;
	uint32_t timeout;
	LPFC_MBOXQ_t *pmboxq  = NULL;
	int mbxstatus = MBX_SUCCESS;
	int i = 0;
	int rc = 0;

	/* no data to return just the return code */
	bsg_reply->reply_payload_rcv_len = 0;

	if (job->request_len < sizeof(struct fc_bsg_request) +
	    sizeof(struct diag_mode_set)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2738 Received DIAG MODE request size:%d "
				"below the minimum size:%d\n",
				job->request_len,
				(int)(sizeof(struct fc_bsg_request) +
				sizeof(struct diag_mode_set)));
		rc = -EINVAL;
		goto job_error;
	}

	rc = lpfc_bsg_diag_mode_enter(phba);
	if (rc)
		goto job_error;

	/* bring the link to diagnostic mode */
	loopback_mode = (struct diag_mode_set *)
		bsg_request->rqst_data.h_vendor.vendor_cmd;
	link_flags = loopback_mode->type;
	timeout = loopback_mode->timeout * 100;

	pmboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmboxq) {
		rc = -ENOMEM;
		goto loopback_mode_exit;
	}
	memset((void *)pmboxq, 0, sizeof(LPFC_MBOXQ_t));
	pmboxq->u.mb.mbxCommand = MBX_DOWN_LINK;
	pmboxq->u.mb.mbxOwner = OWN_HOST;

	mbxstatus = lpfc_sli_issue_mbox_wait(phba, pmboxq, LPFC_MBOX_TMO);

	if ((mbxstatus == MBX_SUCCESS) && (pmboxq->u.mb.mbxStatus == 0)) {
		/* wait for link down before proceeding */
		i = 0;
		while (phba->link_state != LPFC_LINK_DOWN) {
			if (i++ > timeout) {
				rc = -ETIMEDOUT;
				goto loopback_mode_exit;
			}
			msleep(10);
		}

		memset((void *)pmboxq, 0, sizeof(LPFC_MBOXQ_t));
		if (link_flags == INTERNAL_LOOP_BACK)
			pmboxq->u.mb.un.varInitLnk.link_flags = FLAGS_LOCAL_LB;
		else
			pmboxq->u.mb.un.varInitLnk.link_flags =
				FLAGS_TOPOLOGY_MODE_LOOP;

		pmboxq->u.mb.mbxCommand = MBX_INIT_LINK;
		pmboxq->u.mb.mbxOwner = OWN_HOST;

		mbxstatus = lpfc_sli_issue_mbox_wait(phba, pmboxq,
						     LPFC_MBOX_TMO);

		if ((mbxstatus != MBX_SUCCESS) || (pmboxq->u.mb.mbxStatus))
			rc = -ENODEV;
		else {
			spin_lock_irq(&phba->hbalock);
			phba->link_flag |= LS_LOOPBACK_MODE;
			spin_unlock_irq(&phba->hbalock);
			/* wait for the link attention interrupt */
			msleep(100);

			i = 0;
			while (phba->link_state != LPFC_HBA_READY) {
				if (i++ > timeout) {
					rc = -ETIMEDOUT;
					break;
				}

				msleep(10);
			}
		}

	} else
		rc = -ENODEV;

loopback_mode_exit:
	lpfc_bsg_diag_mode_exit(phba);

	/*
	 * Let SLI layer release mboxq if mbox command completed after timeout.
	 */
	if (pmboxq && mbxstatus != MBX_TIMEOUT)
		mempool_free(pmboxq, phba->mbox_mem_pool);

job_error:
	/* make error code available to userspace */
	bsg_reply->result = rc;
	/* complete the job back to userspace if no error */
	if (rc == 0)
		bsg_job_done(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	return rc;
}