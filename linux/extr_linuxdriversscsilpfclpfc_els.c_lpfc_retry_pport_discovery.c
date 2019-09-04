#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_nodelist {int /*<<< orphan*/  nlp_last_elscmd; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_delayfunc; } ;
struct lpfc_hba {TYPE_1__* pport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_FLOGI ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  LPFC_FLOGI ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_cancel_all_vport_retry_delay_timer (struct lpfc_hba*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (TYPE_1__*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_retry_pport_discovery(struct lpfc_hba *phba)
{
	struct lpfc_nodelist *ndlp;
	struct Scsi_Host  *shost;

	/* Cancel the all vports retry delay retry timers */
	lpfc_cancel_all_vport_retry_delay_timer(phba);

	/* If fabric require FLOGI, then re-instantiate physical login */
	ndlp = lpfc_findnode_did(phba->pport, Fabric_DID);
	if (!ndlp)
		return;

	shost = lpfc_shost_from_vport(phba->pport);
	mod_timer(&ndlp->nlp_delayfunc, jiffies + msecs_to_jiffies(1000));
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag |= NLP_DELAY_TMO;
	spin_unlock_irq(shost->host_lock);
	ndlp->nlp_last_elscmd = ELS_CMD_FLOGI;
	phba->pport->port_state = LPFC_FLOGI;
	return;
}