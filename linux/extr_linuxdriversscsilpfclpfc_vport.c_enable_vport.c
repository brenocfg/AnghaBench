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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  load_flag; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct lpfc_hba {scalar_t__ link_state; scalar_t__ fc_topology; int link_flag; int /*<<< orphan*/  pport; } ;
struct fc_vport {scalar_t__ dd_data; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LOADING ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int FC_VPORT_NEEDS_INIT_VPI ; 
 int FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  FC_VPORT_NO_FABRIC_SUPP ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LOG_VPORT ; 
 scalar_t__ LPFC_LINK_UP ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int LS_NPIV_FAB_SUPPORTED ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int VPORT_OK ; 
 struct lpfc_nodelist* lpfc_findnode_did (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_initial_fdisc (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_init_vpi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_vport(struct fc_vport *fc_vport)
{
	struct lpfc_vport *vport = *(struct lpfc_vport **)fc_vport->dd_data;
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_nodelist *ndlp = NULL;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	if ((phba->link_state < LPFC_LINK_UP) ||
	    (phba->fc_topology == LPFC_TOPOLOGY_LOOP)) {
		lpfc_vport_set_state(vport, FC_VPORT_LINKDOWN);
		return VPORT_OK;
	}

	spin_lock_irq(shost->host_lock);
	vport->load_flag |= FC_LOADING;
	if (vport->fc_flag & FC_VPORT_NEEDS_INIT_VPI) {
		spin_unlock_irq(shost->host_lock);
		lpfc_issue_init_vpi(vport);
		goto out;
	}

	vport->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
	spin_unlock_irq(shost->host_lock);

	/* Use the Physical nodes Fabric NDLP to determine if the link is
	 * up and ready to FDISC.
	 */
	ndlp = lpfc_findnode_did(phba->pport, Fabric_DID);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)
	    && ndlp->nlp_state == NLP_STE_UNMAPPED_NODE) {
		if (phba->link_flag & LS_NPIV_FAB_SUPPORTED) {
			lpfc_set_disctmo(vport);
			lpfc_initial_fdisc(vport);
		} else {
			lpfc_vport_set_state(vport, FC_VPORT_NO_FABRIC_SUPP);
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
					 "0264 No NPIV Fabric support\n");
		}
	} else {
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
	}

out:
	lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
			 "1827 Vport Enabled.\n");
	return VPORT_OK;
}