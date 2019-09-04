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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ulp_bde64 {int dummy; } ;
struct lpfc_vport {int /*<<< orphan*/  port_state; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {size_t nlp_rpi; int /*<<< orphan*/  nlp_DID; } ;
struct TYPE_10__ {int /*<<< orphan*/  ndlp; } ;
struct TYPE_11__ {int Fctl; int /*<<< orphan*/  Type; int /*<<< orphan*/  Rctl; scalar_t__ Dfctl; } ;
struct TYPE_12__ {TYPE_3__ hcsw; } ;
struct TYPE_9__ {int bdeSize; int /*<<< orphan*/  bdeFlags; int /*<<< orphan*/  addrLow; int /*<<< orphan*/  addrHigh; scalar_t__ ulpIoTag32; } ;
struct TYPE_13__ {TYPE_4__ w5; TYPE_1__ bdl; } ;
struct TYPE_14__ {TYPE_5__ genreq64; } ;
struct TYPE_16__ {int ulpTimeout; int ulpBdeCount; int ulpLe; size_t ulpContext; int /*<<< orphan*/  ulpIoTag; scalar_t__ ulpCt_l; scalar_t__ ulpCt_h; int /*<<< orphan*/  ulpClass; TYPE_6__ un; int /*<<< orphan*/  ulpCommand; } ;
struct lpfc_iocbq {void (* iocb_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ;int drvrTimeout; int /*<<< orphan*/  retry; struct lpfc_vport* vport; TYPE_2__ context_un; int /*<<< orphan*/ * context2; int /*<<< orphan*/ * context1; int /*<<< orphan*/ * context3; TYPE_8__ iocb; } ;
struct TYPE_15__ {size_t* rpi_ids; } ;
struct lpfc_hba {int fc_ratov; scalar_t__ sli_rev; int sli3_options; TYPE_7__ sli4_hba; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; } ;
typedef  TYPE_8__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_TYPE_BLP_64 ; 
 int /*<<< orphan*/  CLASS3 ; 
 int /*<<< orphan*/  CMD_GEN_REQUEST64_CR ; 
 int /*<<< orphan*/  FC_RCTL_DD_UNSOL_CTL ; 
 int /*<<< orphan*/  FC_TYPE_CT ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LA ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int LPFC_DRVR_TIMEOUT ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int SI ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  putPaddrHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putPaddrLow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_gen_req(struct lpfc_vport *vport, struct lpfc_dmabuf *bmp,
	     struct lpfc_dmabuf *inp, struct lpfc_dmabuf *outp,
	     void (*cmpl) (struct lpfc_hba *, struct lpfc_iocbq *,
		     struct lpfc_iocbq *),
	     struct lpfc_nodelist *ndlp, uint32_t usr_flg, uint32_t num_entry,
	     uint32_t tmo, uint8_t retry)
{
	struct lpfc_hba  *phba = vport->phba;
	IOCB_t *icmd;
	struct lpfc_iocbq *geniocb;
	int rc;

	/* Allocate buffer for  command iocb */
	geniocb = lpfc_sli_get_iocbq(phba);

	if (geniocb == NULL)
		return 1;

	icmd = &geniocb->iocb;
	icmd->un.genreq64.bdl.ulpIoTag32 = 0;
	icmd->un.genreq64.bdl.addrHigh = putPaddrHigh(bmp->phys);
	icmd->un.genreq64.bdl.addrLow = putPaddrLow(bmp->phys);
	icmd->un.genreq64.bdl.bdeFlags = BUFF_TYPE_BLP_64;
	icmd->un.genreq64.bdl.bdeSize = (num_entry * sizeof(struct ulp_bde64));

	if (usr_flg)
		geniocb->context3 = NULL;
	else
		geniocb->context3 = (uint8_t *) bmp;

	/* Save for completion so we can release these resources */
	geniocb->context1 = (uint8_t *) inp;
	geniocb->context2 = (uint8_t *) outp;
	geniocb->context_un.ndlp = lpfc_nlp_get(ndlp);

	/* Fill in payload, bp points to frame payload */
	icmd->ulpCommand = CMD_GEN_REQUEST64_CR;

	/* Fill in rest of iocb */
	icmd->un.genreq64.w5.hcsw.Fctl = (SI | LA);
	icmd->un.genreq64.w5.hcsw.Dfctl = 0;
	icmd->un.genreq64.w5.hcsw.Rctl = FC_RCTL_DD_UNSOL_CTL;
	icmd->un.genreq64.w5.hcsw.Type = FC_TYPE_CT;

	if (!tmo) {
		 /* FC spec states we need 3 * ratov for CT requests */
		tmo = (3 * phba->fc_ratov);
	}
	icmd->ulpTimeout = tmo;
	icmd->ulpBdeCount = 1;
	icmd->ulpLe = 1;
	icmd->ulpClass = CLASS3;
	icmd->ulpContext = ndlp->nlp_rpi;
	if (phba->sli_rev == LPFC_SLI_REV4)
		icmd->ulpContext = phba->sli4_hba.rpi_ids[ndlp->nlp_rpi];

	if (phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) {
		/* For GEN_REQUEST64_CR, use the RPI */
		icmd->ulpCt_h = 0;
		icmd->ulpCt_l = 0;
	}

	/* Issue GEN REQ IOCB for NPORT <did> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0119 Issue GEN REQ IOCB to NPORT x%x "
			 "Data: x%x x%x\n",
			 ndlp->nlp_DID, icmd->ulpIoTag,
			 vport->port_state);
	geniocb->iocb_cmpl = cmpl;
	geniocb->drvrTimeout = icmd->ulpTimeout + LPFC_DRVR_TIMEOUT;
	geniocb->vport = vport;
	geniocb->retry = retry;
	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, geniocb, 0);

	if (rc == IOCB_ERROR) {
		lpfc_sli_release_iocbq(phba, geniocb);
		return 1;
	}

	return 0;
}