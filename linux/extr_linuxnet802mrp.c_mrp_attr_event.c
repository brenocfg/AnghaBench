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
struct mrp_attr {size_t state; } ;
struct mrp_applicant {int dummy; } ;
typedef  enum mrp_event { ____Placeholder_mrp_event } mrp_event ;
typedef  enum mrp_applicant_state { ____Placeholder_mrp_applicant_state } mrp_applicant_state ;

/* Variables and functions */
 int MRP_APPLICANT_INVALID ; 
 int MRP_EVENT_TX ; 
#define  MRP_TX_ACTION_NONE 133 
#define  MRP_TX_ACTION_S_IN_OPTIONAL 132 
#define  MRP_TX_ACTION_S_JOIN_IN 131 
#define  MRP_TX_ACTION_S_JOIN_IN_OPTIONAL 130 
#define  MRP_TX_ACTION_S_LV 129 
#define  MRP_TX_ACTION_S_NEW 128 
 int /*<<< orphan*/  MRP_VECATTR_EVENT_JOIN_IN ; 
 int /*<<< orphan*/  MRP_VECATTR_EVENT_LV ; 
 int /*<<< orphan*/  MRP_VECATTR_EVENT_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int** mrp_applicant_state_table ; 
 int /*<<< orphan*/  mrp_attr_destroy (struct mrp_applicant*,struct mrp_attr*) ; 
 int /*<<< orphan*/  mrp_pdu_append_vecattr_event (struct mrp_applicant*,struct mrp_attr*,int /*<<< orphan*/ ) ; 
 int* mrp_tx_action_table ; 

__attribute__((used)) static void mrp_attr_event(struct mrp_applicant *app,
			   struct mrp_attr *attr, enum mrp_event event)
{
	enum mrp_applicant_state state;

	state = mrp_applicant_state_table[attr->state][event];
	if (state == MRP_APPLICANT_INVALID) {
		WARN_ON(1);
		return;
	}

	if (event == MRP_EVENT_TX) {
		/* When appending the attribute fails, don't update its state
		 * in order to retry at the next TX event.
		 */

		switch (mrp_tx_action_table[attr->state]) {
		case MRP_TX_ACTION_NONE:
		case MRP_TX_ACTION_S_JOIN_IN_OPTIONAL:
		case MRP_TX_ACTION_S_IN_OPTIONAL:
			break;
		case MRP_TX_ACTION_S_NEW:
			if (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_NEW) < 0)
				return;
			break;
		case MRP_TX_ACTION_S_JOIN_IN:
			if (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_JOIN_IN) < 0)
				return;
			break;
		case MRP_TX_ACTION_S_LV:
			if (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_LV) < 0)
				return;
			/* As a pure applicant, sending a leave message
			 * implies that the attribute was unregistered and
			 * can be destroyed.
			 */
			mrp_attr_destroy(app, attr);
			return;
		default:
			WARN_ON(1);
		}
	}

	attr->state = state;
}