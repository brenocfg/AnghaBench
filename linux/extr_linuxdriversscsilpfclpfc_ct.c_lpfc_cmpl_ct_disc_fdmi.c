#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct lpfc_vport {void* fdmi_port_mask; int /*<<< orphan*/  port_type; void* fdmi_hba_mask; } ;
struct TYPE_5__ {scalar_t__ CmdRsp; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct lpfc_sli_ct_request {TYPE_2__ CommandResponse; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_7__ {int* ulpWord; } ;
struct TYPE_8__ {scalar_t__ ulpStatus; TYPE_3__ un; } ;
struct lpfc_iocbq {int /*<<< orphan*/  retry; TYPE_4__ iocb; struct lpfc_dmabuf* context2; struct lpfc_dmabuf* context1; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {struct lpfc_sli_ct_request* virt; } ;
typedef  TYPE_4__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDMI_DID ; 
 int IOCB_ERROR ; 
#define  IOERR_ABORT_IN_PROGRESS 138 
#define  IOERR_ILLEGAL_COMMAND 137 
#define  IOERR_ILLEGAL_FRAME 136 
#define  IOERR_NO_RESOURCES 135 
 int IOERR_PARAM_MASK ; 
#define  IOERR_SEQUENCE_TIMEOUT 134 
#define  IOERR_SLI_ABORTED 133 
 scalar_t__ IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 void* LPFC_FDMI1_HBA_ATTR ; 
 void* LPFC_FDMI1_PORT_ATTR ; 
 void* LPFC_FDMI2_HBA_ATTR ; 
 void* LPFC_FDMI2_PORT_ATTR ; 
 void* LPFC_FDMI2_SMART_ATTR ; 
 int /*<<< orphan*/  LPFC_FDMI_MAX_RETRY ; 
 int /*<<< orphan*/  LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  SLI_CT_RESPONSE_FS_RJT ; 
#define  SLI_MGMT_DHBA 132 
#define  SLI_MGMT_DPRT 131 
#define  SLI_MGMT_RHBA 130 
#define  SLI_MGMT_RPA 129 
#define  SLI_MGMT_RPRT 128 
 int be16_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ct_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_fdmi_cmd (struct lpfc_vport*,struct lpfc_nodelist*,int const,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_ct_disc_fdmi(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		       struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct lpfc_dmabuf *inp = cmdiocb->context1;
	struct lpfc_dmabuf *outp = cmdiocb->context2;
	struct lpfc_sli_ct_request *CTcmd = inp->virt;
	struct lpfc_sli_ct_request *CTrsp = outp->virt;
	uint16_t fdmi_cmd = CTcmd->CommandResponse.bits.CmdRsp;
	uint16_t fdmi_rsp = CTrsp->CommandResponse.bits.CmdRsp;
	IOCB_t *irsp = &rspiocb->iocb;
	struct lpfc_nodelist *ndlp;
	uint32_t latt, cmd, err;

	latt = lpfc_els_chk_latt(vport);
	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		"FDMI cmpl:       status:x%x/x%x latt:%d",
		irsp->ulpStatus, irsp->un.ulpWord[4], latt);

	if (latt || irsp->ulpStatus) {

		/* Look for a retryable error */
		if (irsp->ulpStatus == IOSTAT_LOCAL_REJECT) {
			switch ((irsp->un.ulpWord[4] & IOERR_PARAM_MASK)) {
			case IOERR_SLI_ABORTED:
			case IOERR_ABORT_IN_PROGRESS:
			case IOERR_SEQUENCE_TIMEOUT:
			case IOERR_ILLEGAL_FRAME:
			case IOERR_NO_RESOURCES:
			case IOERR_ILLEGAL_COMMAND:
				cmdiocb->retry++;
				if (cmdiocb->retry >= LPFC_FDMI_MAX_RETRY)
					break;

				/* Retry the same FDMI command */
				err = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING,
							  cmdiocb, 0);
				if (err == IOCB_ERROR)
					break;
				return;
			default:
				break;
			}
		}

		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0229 FDMI cmd %04x failed, latt = %d "
				 "ulpStatus: x%x, rid x%x\n",
				 be16_to_cpu(fdmi_cmd), latt, irsp->ulpStatus,
				 irsp->un.ulpWord[4]);
	}
	lpfc_ct_free_iocb(phba, cmdiocb);

	ndlp = lpfc_findnode_did(vport, FDMI_DID);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		return;

	/* Check for a CT LS_RJT response */
	cmd =  be16_to_cpu(fdmi_cmd);
	if (fdmi_rsp == cpu_to_be16(SLI_CT_RESPONSE_FS_RJT)) {
		/* FDMI rsp failed */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0220 FDMI cmd failed FS_RJT Data: x%x", cmd);

		/* Should we fallback to FDMI-2 / FDMI-1 ? */
		switch (cmd) {
		case SLI_MGMT_RHBA:
			if (vport->fdmi_hba_mask == LPFC_FDMI2_HBA_ATTR) {
				/* Fallback to FDMI-1 */
				vport->fdmi_hba_mask = LPFC_FDMI1_HBA_ATTR;
				vport->fdmi_port_mask = LPFC_FDMI1_PORT_ATTR;
				/* Start over */
				lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_DHBA, 0);
			}
			return;

		case SLI_MGMT_RPRT:
			if (vport->fdmi_port_mask == LPFC_FDMI2_PORT_ATTR) {
				/* Fallback to FDMI-1 */
				vport->fdmi_port_mask = LPFC_FDMI1_PORT_ATTR;
				/* Start over */
				lpfc_fdmi_cmd(vport, ndlp, cmd, 0);
			}
			if (vport->fdmi_port_mask == LPFC_FDMI2_SMART_ATTR) {
				vport->fdmi_port_mask = LPFC_FDMI2_PORT_ATTR;
				/* Retry the same command */
				lpfc_fdmi_cmd(vport, ndlp, cmd, 0);
			}
			return;

		case SLI_MGMT_RPA:
			if (vport->fdmi_port_mask == LPFC_FDMI2_PORT_ATTR) {
				/* Fallback to FDMI-1 */
				vport->fdmi_hba_mask = LPFC_FDMI1_HBA_ATTR;
				vport->fdmi_port_mask = LPFC_FDMI1_PORT_ATTR;
				/* Start over */
				lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_DHBA, 0);
			}
			if (vport->fdmi_port_mask == LPFC_FDMI2_SMART_ATTR) {
				vport->fdmi_port_mask = LPFC_FDMI2_PORT_ATTR;
				/* Retry the same command */
				lpfc_fdmi_cmd(vport, ndlp, cmd, 0);
			}
			return;
		}
	}

	/*
	 * On success, need to cycle thru FDMI registration for discovery
	 * DHBA -> DPRT -> RHBA -> RPA  (physical port)
	 * DPRT -> RPRT (vports)
	 */
	switch (cmd) {
	case SLI_MGMT_RHBA:
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RPA, 0);
		break;

	case SLI_MGMT_DHBA:
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_DPRT, 0);
		break;

	case SLI_MGMT_DPRT:
		if (vport->port_type == LPFC_PHYSICAL_PORT)
			lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RHBA, 0);
		else
			lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RPRT, 0);
		break;
	}
	return;
}