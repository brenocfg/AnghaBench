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
struct lpfc_vport {int /*<<< orphan*/  port_state; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  LPFC_FLOGI ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enqueue_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_issue_els_flogi (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 

int
lpfc_initial_flogi(struct lpfc_vport *vport)
{
	struct lpfc_nodelist *ndlp;

	vport->port_state = LPFC_FLOGI;
	lpfc_set_disctmo(vport);

	/* First look for the Fabric ndlp */
	ndlp = lpfc_findnode_did(vport, Fabric_DID);
	if (!ndlp) {
		/* Cannot find existing Fabric ndlp, so allocate a new one */
		ndlp = lpfc_nlp_init(vport, Fabric_DID);
		if (!ndlp)
			return 0;
		/* Set the node type */
		ndlp->nlp_type |= NLP_FABRIC;
		/* Put ndlp onto node list */
		lpfc_enqueue_node(vport, ndlp);
	} else if (!NLP_CHK_NODE_ACT(ndlp)) {
		/* re-setup ndlp without removing from node list */
		ndlp = lpfc_enable_node(vport, ndlp, NLP_STE_UNUSED_NODE);
		if (!ndlp)
			return 0;
	}

	if (lpfc_issue_els_flogi(vport, ndlp, 0)) {
		/* This decrement of reference count to node shall kick off
		 * the release of the node.
		 */
		lpfc_nlp_put(ndlp);
		return 0;
	}
	return 1;
}