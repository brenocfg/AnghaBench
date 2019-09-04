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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int fc_flag; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; } ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_RSCN_DEFERRED ; 
 int NLP_NODEV_REMOVE ; 
 int NLP_NPR_2B_DISC ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PRLI_ISSUE ; 
 int /*<<< orphan*/  lpfc_disc_set_adisc (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_abort (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_device_recov_prli_issue(struct lpfc_vport *vport,
			     struct lpfc_nodelist *ndlp,
			     void *arg,
			     uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;

	/* Don't do anything that will mess up processing of the
	 * previous RSCN.
	 */
	if (vport->fc_flag & FC_RSCN_DEFERRED)
		return ndlp->nlp_state;

	/* software abort outstanding PRLI */
	lpfc_els_abort(phba, ndlp);

	ndlp->nlp_prev_state = NLP_STE_PRLI_ISSUE;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~(NLP_NODEV_REMOVE | NLP_NPR_2B_DISC);
	spin_unlock_irq(shost->host_lock);
	lpfc_disc_set_adisc(vport, ndlp);
	return ndlp->nlp_state;
}