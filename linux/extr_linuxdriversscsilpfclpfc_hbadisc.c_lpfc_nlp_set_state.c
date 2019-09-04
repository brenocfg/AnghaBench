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
struct lpfc_vport {int /*<<< orphan*/  fc_nodes; } ;
struct lpfc_nodelist {int nlp_state; int /*<<< orphan*/  nlp_listp; int /*<<< orphan*/  nlp_type; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  name2 ;
typedef  int /*<<< orphan*/  name1 ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_NODE ; 
 int /*<<< orphan*/  NLP_FC_NODE ; 
 int NLP_STE_NPR_NODE ; 
 int NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  NLP_TGT_NO_SCSIID ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpfc_nlp_counters (struct lpfc_vport*,int,int) ; 
 int /*<<< orphan*/  lpfc_nlp_state_cleanup (struct lpfc_vport*,struct lpfc_nodelist*,int,int) ; 
 int /*<<< orphan*/  lpfc_nlp_state_name (char*,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_nlp_set_state(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		   int state)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	int  old_state = ndlp->nlp_state;
	char name1[16], name2[16];

	lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
			 "0904 NPort state transition x%06x, %s -> %s\n",
			 ndlp->nlp_DID,
			 lpfc_nlp_state_name(name1, sizeof(name1), old_state),
			 lpfc_nlp_state_name(name2, sizeof(name2), state));

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_NODE,
		"node statechg    did:x%x old:%d ste:%d",
		ndlp->nlp_DID, old_state, state);

	if (old_state == NLP_STE_NPR_NODE &&
	    state != NLP_STE_NPR_NODE)
		lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if (old_state == NLP_STE_UNMAPPED_NODE) {
		ndlp->nlp_flag &= ~NLP_TGT_NO_SCSIID;
		ndlp->nlp_type &= ~NLP_FC_NODE;
	}

	if (list_empty(&ndlp->nlp_listp)) {
		spin_lock_irq(shost->host_lock);
		list_add_tail(&ndlp->nlp_listp, &vport->fc_nodes);
		spin_unlock_irq(shost->host_lock);
	} else if (old_state)
		lpfc_nlp_counters(vport, old_state, -1);

	ndlp->nlp_state = state;
	lpfc_nlp_counters(vport, state, 1);
	lpfc_nlp_state_cleanup(vport, ndlp, old_state, state);
}