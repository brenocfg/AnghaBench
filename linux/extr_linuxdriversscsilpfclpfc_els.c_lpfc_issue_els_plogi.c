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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_8__ {void* flags; void* vid; } ;
struct TYPE_9__ {TYPE_3__ vv; int /*<<< orphan*/  vendorVersion; } ;
struct TYPE_7__ {int altBbCredit; scalar_t__ fcphLow; scalar_t__ fcphHigh; int valid_vendor_ver_level; int bbRcvSizeMsb; } ;
struct serv_parm {TYPE_4__ un; TYPE_2__ cmn; } ;
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  fc_sparam; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; scalar_t__ context2; } ;
struct TYPE_10__ {int /*<<< orphan*/  elsXmitPLOGI; } ;
struct TYPE_6__ {int sli_flag; } ;
struct lpfc_hba {TYPE_5__ fc_stat; TYPE_1__ sli; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 int FC_FABRIC ; 
 scalar_t__ FC_PH3 ; 
 scalar_t__ FC_PH_4_3 ; 
 int FC_PUBLIC_LOOP ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int LPFC_SLI_SUPPRESS_RSP ; 
 int /*<<< orphan*/  LPFC_VV_EMLX_ID ; 
 int /*<<< orphan*/  LPFC_VV_SUPPRESS_RSP ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FCP_PRLI_RJT ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cmpl_els_plogi ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int
lpfc_issue_els_plogi(struct lpfc_vport *vport, uint32_t did, uint8_t retry)
{
	struct lpfc_hba  *phba = vport->phba;
	struct Scsi_Host *shost;
	struct serv_parm *sp;
	struct lpfc_nodelist *ndlp;
	struct lpfc_iocbq *elsiocb;
	uint8_t *pcmd;
	uint16_t cmdsize;
	int ret;

	ndlp = lpfc_findnode_did(vport, did);
	if (ndlp && !NLP_CHK_NODE_ACT(ndlp))
		ndlp = NULL;

	/* If ndlp is not NULL, we will bump the reference count on it */
	cmdsize = (sizeof(uint32_t) + sizeof(struct serv_parm));
	elsiocb = lpfc_prep_els_iocb(vport, 1, cmdsize, retry, ndlp, did,
				     ELS_CMD_PLOGI);
	if (!elsiocb)
		return 1;

	shost = lpfc_shost_from_vport(vport);
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~NLP_FCP_PRLI_RJT;
	spin_unlock_irq(shost->host_lock);

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

	/* For PLOGI request, remainder of payload is service parameters */
	*((uint32_t *) (pcmd)) = ELS_CMD_PLOGI;
	pcmd += sizeof(uint32_t);
	memcpy(pcmd, &vport->fc_sparam, sizeof(struct serv_parm));
	sp = (struct serv_parm *) pcmd;

	/*
	 * If we are a N-port connected to a Fabric, fix-up paramm's so logins
	 * to device on remote loops work.
	 */
	if ((vport->fc_flag & FC_FABRIC) && !(vport->fc_flag & FC_PUBLIC_LOOP))
		sp->cmn.altBbCredit = 1;

	if (sp->cmn.fcphLow < FC_PH_4_3)
		sp->cmn.fcphLow = FC_PH_4_3;

	if (sp->cmn.fcphHigh < FC_PH3)
		sp->cmn.fcphHigh = FC_PH3;

	sp->cmn.valid_vendor_ver_level = 0;
	memset(sp->un.vendorVersion, 0, sizeof(sp->un.vendorVersion));
	sp->cmn.bbRcvSizeMsb &= 0xF;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Issue PLOGI:     did:x%x",
		did, 0, 0);

	/* If our firmware supports this feature, convey that
	 * information to the target using the vendor specific field.
	 */
	if (phba->sli.sli_flag & LPFC_SLI_SUPPRESS_RSP) {
		sp->cmn.valid_vendor_ver_level = 1;
		sp->un.vv.vid = cpu_to_be32(LPFC_VV_EMLX_ID);
		sp->un.vv.flags = cpu_to_be32(LPFC_VV_SUPPRESS_RSP);
	}

	phba->fc_stat.elsXmitPLOGI++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_plogi;
	ret = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);

	if (ret == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}