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
struct bfa_fcs_rport_s {int pwwn; int pid; int /*<<< orphan*/  fcs; } ;
struct bfa_fcs_rpf_s {struct bfa_fcs_rport_s* rport; } ;
typedef  enum rpf_event { ____Placeholder_rpf_event } rpf_event ;

/* Variables and functions */
#define  RPFSM_EVENT_RPORT_OFFLINE 129 
#define  RPFSM_EVENT_RPORT_ONLINE 128 
 int /*<<< orphan*/  bfa_fcs_rpf_send_rpsc2 (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_rpsc_sending ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rpf_sm_offline(struct bfa_fcs_rpf_s *rpf, enum rpf_event event)
{
	struct bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPFSM_EVENT_RPORT_ONLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_sending);
		bfa_fcs_rpf_send_rpsc2(rpf, NULL);
		break;

	case RPFSM_EVENT_RPORT_OFFLINE:
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}