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
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int NLP_NODEV_REMOVE ; 
 int NLP_NPR_2B_DISC ; 
 int /*<<< orphan*/  NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  lpfc_disc_set_adisc (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_device_recov_mapped_node(struct lpfc_vport *vport,
			      struct lpfc_nodelist *ndlp,
			      void *arg,
			      uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	ndlp->nlp_prev_state = NLP_STE_MAPPED_NODE;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~(NLP_NODEV_REMOVE | NLP_NPR_2B_DISC);
	spin_unlock_irq(shost->host_lock);
	lpfc_disc_set_adisc(vport, ndlp);
	return ndlp->nlp_state;
}