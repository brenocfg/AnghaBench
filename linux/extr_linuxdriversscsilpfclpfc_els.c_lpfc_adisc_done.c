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
struct lpfc_vport {int fc_flag; scalar_t__ port_state; scalar_t__ num_disc_nodes; scalar_t__ fc_npr_cnt; struct lpfc_hba* phba; } ;
struct lpfc_hba {int sli3_options; scalar_t__ sli_rev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_ABORT_DISCOVERY ; 
 int FC_NDISC_ACTIVE ; 
 int FC_RSCN_MODE ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_VPORT_READY ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_disc_plogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_end_rscn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_clear_la (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_reg_vpi (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_rscn_disc (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_adisc_done(struct lpfc_vport *vport)
{
	struct Scsi_Host   *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba   *phba = vport->phba;

	/*
	 * For NPIV, cmpl_reg_vpi will set port_state to READY,
	 * and continue discovery.
	 */
	if ((phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) &&
	    !(vport->fc_flag & FC_RSCN_MODE) &&
	    (phba->sli_rev < LPFC_SLI_REV4)) {
		/* The ADISCs are complete.  Doesn't matter if they
		 * succeeded or failed because the ADISC completion
		 * routine guarantees to call the state machine and
		 * the RPI is either unregistered (failed ADISC response)
		 * or the RPI is still valid and the node is marked
		 * mapped for a target.  The exchanges should be in the
		 * correct state. This code is specific to SLI3.
		 */
		lpfc_issue_clear_la(phba, vport);
		lpfc_issue_reg_vpi(phba, vport);
		return;
	}
	/*
	* For SLI2, we need to set port_state to READY
	* and continue discovery.
	*/
	if (vport->port_state < LPFC_VPORT_READY) {
		/* If we get here, there is nothing to ADISC */
		lpfc_issue_clear_la(phba, vport);
		if (!(vport->fc_flag & FC_ABORT_DISCOVERY)) {
			vport->num_disc_nodes = 0;
			/* go thru NPR list, issue ELS PLOGIs */
			if (vport->fc_npr_cnt)
				lpfc_els_disc_plogi(vport);
			if (!vport->num_disc_nodes) {
				spin_lock_irq(shost->host_lock);
				vport->fc_flag &= ~FC_NDISC_ACTIVE;
				spin_unlock_irq(shost->host_lock);
				lpfc_can_disctmo(vport);
				lpfc_end_rscn(vport);
			}
		}
		vport->port_state = LPFC_VPORT_READY;
	} else
		lpfc_rscn_disc(vport);
}