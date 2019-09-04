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
struct sk_buff {int dummy; } ;
struct llc_sap_state_trans {int /*<<< orphan*/  next_state; } ;
struct llc_sap {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_NR_SAP_STATES ; 
 int llc_exec_sap_trans_actions (struct llc_sap*,struct llc_sap_state_trans*,struct sk_buff*) ; 
 struct llc_sap_state_trans* llc_find_sap_trans (struct llc_sap*,struct sk_buff*) ; 

__attribute__((used)) static int llc_sap_next_state(struct llc_sap *sap, struct sk_buff *skb)
{
	int rc = 1;
	struct llc_sap_state_trans *trans;

	if (sap->state > LLC_NR_SAP_STATES)
		goto out;
	trans = llc_find_sap_trans(sap, skb);
	if (!trans)
		goto out;
	/*
	 * Got the state to which we next transition; perform the actions
	 * associated with this transition before actually transitioning to the
	 * next state
	 */
	rc = llc_exec_sap_trans_actions(sap, trans, skb);
	if (rc)
		goto out;
	/*
	 * Transition SAP to next state if all actions execute successfully
	 */
	sap->state = trans->next_state;
out:
	return rc;
}