#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_vport {int fc_flag; } ;
struct lpfc_nodelist {int nlp_last_elscmd; int nlp_flag; int nlp_retry; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_delayfunc; struct lpfc_vport* vport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
#define  ELS_CMD_ADISC 134 
#define  ELS_CMD_FDISC 133 
#define  ELS_CMD_FLOGI 132 
#define  ELS_CMD_LOGO 131 
#define  ELS_CMD_NVMEPRLI 130 
#define  ELS_CMD_PLOGI 129 
#define  ELS_CMD_PRLI 128 
 int FC_VPORT_NEEDS_INIT_VPI ; 
 int NLP_DELAY_TMO ; 
 int /*<<< orphan*/  NLP_STE_ADISC_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_LOGO_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_PRLI_ISSUE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_issue_els_adisc (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_fdisc (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_flogi (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_logo (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_prli (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_els_retry_delay_handler(struct lpfc_nodelist *ndlp)
{
	struct lpfc_vport *vport = ndlp->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	uint32_t cmd, retry;

	spin_lock_irq(shost->host_lock);
	cmd = ndlp->nlp_last_elscmd;
	ndlp->nlp_last_elscmd = 0;

	if (!(ndlp->nlp_flag & NLP_DELAY_TMO)) {
		spin_unlock_irq(shost->host_lock);
		return;
	}

	ndlp->nlp_flag &= ~NLP_DELAY_TMO;
	spin_unlock_irq(shost->host_lock);
	/*
	 * If a discovery event readded nlp_delayfunc after timer
	 * firing and before processing the timer, cancel the
	 * nlp_delayfunc.
	 */
	del_timer_sync(&ndlp->nlp_delayfunc);
	retry = ndlp->nlp_retry;
	ndlp->nlp_retry = 0;

	switch (cmd) {
	case ELS_CMD_FLOGI:
		lpfc_issue_els_flogi(vport, ndlp, retry);
		break;
	case ELS_CMD_PLOGI:
		if (!lpfc_issue_els_plogi(vport, ndlp->nlp_DID, retry)) {
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);
		}
		break;
	case ELS_CMD_ADISC:
		if (!lpfc_issue_els_adisc(vport, ndlp, retry)) {
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_ADISC_ISSUE);
		}
		break;
	case ELS_CMD_PRLI:
	case ELS_CMD_NVMEPRLI:
		if (!lpfc_issue_els_prli(vport, ndlp, retry)) {
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PRLI_ISSUE);
		}
		break;
	case ELS_CMD_LOGO:
		if (!lpfc_issue_els_logo(vport, ndlp, retry)) {
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_LOGO_ISSUE);
		}
		break;
	case ELS_CMD_FDISC:
		if (!(vport->fc_flag & FC_VPORT_NEEDS_INIT_VPI))
			lpfc_issue_els_fdisc(vport, ndlp, retry);
		break;
	}
	return;
}