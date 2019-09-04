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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct lpfc_vport {int fc_flag; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; scalar_t__ context2; } ;
struct TYPE_3__ {int /*<<< orphan*/  elsXmitSCR; } ;
struct lpfc_hba {TYPE_1__ fc_stat; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct TYPE_4__ {int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_SCR ; 
 int FC_PT2PT ; 
 scalar_t__ IOCB_ERROR ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  SCR_FUNC_FULL ; 
 int /*<<< orphan*/  lpfc_cmpl_els_cmd ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enqueue_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
lpfc_issue_els_scr(struct lpfc_vport *vport, uint32_t nportid, uint8_t retry)
{
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_iocbq *elsiocb;
	uint8_t *pcmd;
	uint16_t cmdsize;
	struct lpfc_nodelist *ndlp;

	cmdsize = (sizeof(uint32_t) + sizeof(SCR));

	ndlp = lpfc_findnode_did(vport, nportid);
	if (!ndlp) {
		ndlp = lpfc_nlp_init(vport, nportid);
		if (!ndlp)
			return 1;
		lpfc_enqueue_node(vport, ndlp);
	} else if (!NLP_CHK_NODE_ACT(ndlp)) {
		ndlp = lpfc_enable_node(vport, ndlp, NLP_STE_UNUSED_NODE);
		if (!ndlp)
			return 1;
	}

	elsiocb = lpfc_prep_els_iocb(vport, 1, cmdsize, retry, ndlp,
				     ndlp->nlp_DID, ELS_CMD_SCR);

	if (!elsiocb) {
		/* This will trigger the release of the node just
		 * allocated
		 */
		lpfc_nlp_put(ndlp);
		return 1;
	}

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

	*((uint32_t *) (pcmd)) = ELS_CMD_SCR;
	pcmd += sizeof(uint32_t);

	/* For SCR, remainder of payload is SCR parameter page */
	memset(pcmd, 0, sizeof(SCR));
	((SCR *) pcmd)->Function = SCR_FUNC_FULL;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Issue SCR:       did:x%x",
		ndlp->nlp_DID, 0, 0);

	phba->fc_stat.elsXmitSCR++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_cmd;
	if (lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0) ==
	    IOCB_ERROR) {
		/* The additional lpfc_nlp_put will cause the following
		 * lpfc_els_free_iocb routine to trigger the rlease of
		 * the node.
		 */
		lpfc_nlp_put(ndlp);
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	/* This will cause the callback-function lpfc_cmpl_els_cmd to
	 * trigger the release of node.
	 */
	if (!(vport->fc_flag & FC_PT2PT))
		lpfc_nlp_put(ndlp);
	return 0;
}