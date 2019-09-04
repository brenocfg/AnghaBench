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
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDMI_DID ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_start_fdmi(struct lpfc_vport *vport)
{
	struct lpfc_nodelist *ndlp;

	/* If this is the first time, allocate an ndlp and initialize
	 * it. Otherwise, make sure the node is enabled and then do the
	 * login.
	 */
	ndlp = lpfc_findnode_did(vport, FDMI_DID);
	if (!ndlp) {
		ndlp = lpfc_nlp_init(vport, FDMI_DID);
		if (ndlp) {
			ndlp->nlp_type |= NLP_FABRIC;
		} else {
			return;
		}
	}
	if (!NLP_CHK_NODE_ACT(ndlp))
		ndlp = lpfc_enable_node(vport, ndlp, NLP_STE_NPR_NODE);

	if (ndlp) {
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);
		lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0);
	}
}