#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int nlp_type; int /*<<< orphan*/  nlp_state; void* nlp_prev_state; int /*<<< orphan*/  nlp_portname; int /*<<< orphan*/  nlp_nodename; int /*<<< orphan*/  nlp_last_elscmd; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_delayfunc; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_5__ {scalar_t__ ulpStatus; } ;
struct TYPE_4__ {struct lpfc_iocbq* rsp_iocb; } ;
struct lpfc_iocbq {TYPE_2__ iocb; TYPE_1__ context_un; } ;
struct lpfc_hba {scalar_t__ sli_rev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  portName; int /*<<< orphan*/  nodeName; } ;
typedef  TYPE_2__ IOCB_t ;
typedef  TYPE_3__ ADISC ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 int NLP_FCP_TARGET ; 
 void* NLP_STE_ADISC_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_check_adisc (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_check_elscmpl_iocb (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli4_resume_rpi (struct lpfc_nodelist*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_unreg_rpi (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_cmpl_adisc_adisc_issue(struct lpfc_vport *vport,
			    struct lpfc_nodelist *ndlp,
			    void *arg, uint32_t evt)
{
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_iocbq *cmdiocb, *rspiocb;
	IOCB_t *irsp;
	ADISC *ap;
	int rc;

	cmdiocb = (struct lpfc_iocbq *) arg;
	rspiocb = cmdiocb->context_un.rsp_iocb;

	ap = (ADISC *)lpfc_check_elscmpl_iocb(phba, cmdiocb, rspiocb);
	irsp = &rspiocb->iocb;

	if ((irsp->ulpStatus) ||
	    (!lpfc_check_adisc(vport, ndlp, &ap->nodeName, &ap->portName))) {
		/* 1 sec timeout */
		mod_timer(&ndlp->nlp_delayfunc,
			  jiffies + msecs_to_jiffies(1000));
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_DELAY_TMO;
		spin_unlock_irq(shost->host_lock);
		ndlp->nlp_last_elscmd = ELS_CMD_PLOGI;

		memset(&ndlp->nlp_nodename, 0, sizeof(struct lpfc_name));
		memset(&ndlp->nlp_portname, 0, sizeof(struct lpfc_name));

		ndlp->nlp_prev_state = NLP_STE_ADISC_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		lpfc_unreg_rpi(vport, ndlp);
		return ndlp->nlp_state;
	}

	if (phba->sli_rev == LPFC_SLI_REV4) {
		rc = lpfc_sli4_resume_rpi(ndlp, NULL, NULL);
		if (rc) {
			/* Stay in state and retry. */
			ndlp->nlp_prev_state = NLP_STE_ADISC_ISSUE;
			return ndlp->nlp_state;
		}
	}

	if (ndlp->nlp_type & NLP_FCP_TARGET) {
		ndlp->nlp_prev_state = NLP_STE_ADISC_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_MAPPED_NODE);
	} else {
		ndlp->nlp_prev_state = NLP_STE_ADISC_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNMAPPED_NODE);
	}

	return ndlp->nlp_state;
}