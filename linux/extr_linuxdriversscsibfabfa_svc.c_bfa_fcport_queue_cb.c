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
struct bfa_fcport_s {TYPE_1__* bfa; int /*<<< orphan*/  event_cbarg; int /*<<< orphan*/  (* event_cbfn ) (int /*<<< orphan*/ ,int) ;} ;
struct bfa_fcport_ln_s {int ln_event; int /*<<< orphan*/  ln_qe; struct bfa_fcport_s* fcport; } ;
typedef  enum bfa_port_linkstate { ____Placeholder_bfa_port_linkstate } bfa_port_linkstate ;
struct TYPE_2__ {scalar_t__ fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT_LN_SM_NOTIFICATION ; 
 int /*<<< orphan*/  __bfa_cb_fcport_event ; 
 int /*<<< orphan*/  bfa_cb_queue (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcport_ln_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcport_ln_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_queue_cb(struct bfa_fcport_ln_s *ln, enum bfa_port_linkstate event)
{
	struct bfa_fcport_s *fcport = ln->fcport;

	if (fcport->bfa->fcs) {
		fcport->event_cbfn(fcport->event_cbarg, event);
		bfa_sm_send_event(ln, BFA_FCPORT_LN_SM_NOTIFICATION);
	} else {
		ln->ln_event = event;
		bfa_cb_queue(fcport->bfa, &ln->ln_qe,
			__bfa_cb_fcport_event, ln);
	}
}