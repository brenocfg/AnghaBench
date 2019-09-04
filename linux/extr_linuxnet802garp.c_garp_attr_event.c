#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct garp_attr {size_t state; } ;
struct garp_applicant {int dummy; } ;
typedef  enum garp_event { ____Placeholder_garp_event } garp_event ;
typedef  enum garp_applicant_state { ____Placeholder_garp_applicant_state } garp_applicant_state ;
struct TYPE_2__ {int state; int action; } ;

/* Variables and functions */
#define  GARP_ACTION_NONE 130 
#define  GARP_ACTION_S_JOIN_IN 129 
#define  GARP_ACTION_S_LEAVE_EMPTY 128 
 int GARP_APPLICANT_INVALID ; 
 int /*<<< orphan*/  GARP_JOIN_IN ; 
 int /*<<< orphan*/  GARP_LEAVE_EMPTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__** garp_applicant_state_table ; 
 int /*<<< orphan*/  garp_attr_destroy (struct garp_applicant*,struct garp_attr*) ; 
 int /*<<< orphan*/  garp_pdu_append_attr (struct garp_applicant*,struct garp_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void garp_attr_event(struct garp_applicant *app,
			    struct garp_attr *attr, enum garp_event event)
{
	enum garp_applicant_state state;

	state = garp_applicant_state_table[attr->state][event].state;
	if (state == GARP_APPLICANT_INVALID)
		return;

	switch (garp_applicant_state_table[attr->state][event].action) {
	case GARP_ACTION_NONE:
		break;
	case GARP_ACTION_S_JOIN_IN:
		/* When appending the attribute fails, don't update state in
		 * order to retry on next TRANSMIT_PDU event. */
		if (garp_pdu_append_attr(app, attr, GARP_JOIN_IN) < 0)
			return;
		break;
	case GARP_ACTION_S_LEAVE_EMPTY:
		garp_pdu_append_attr(app, attr, GARP_LEAVE_EMPTY);
		/* As a pure applicant, sending a leave message implies that
		 * the attribute was unregistered and can be destroyed. */
		garp_attr_destroy(app, attr);
		return;
	default:
		WARN_ON(1);
	}

	attr->state = state;
}