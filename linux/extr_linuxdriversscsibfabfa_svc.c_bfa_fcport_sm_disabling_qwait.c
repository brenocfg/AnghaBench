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
struct bfa_fcport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  reqq_wait; } ;
typedef  enum bfa_fcport_sm_event { ____Placeholder_bfa_fcport_sm_event } bfa_fcport_sm_event ;

/* Variables and functions */
#define  BFA_FCPORT_SM_DISABLE 135 
#define  BFA_FCPORT_SM_ENABLE 134 
#define  BFA_FCPORT_SM_FAA_MISCONFIG 133 
#define  BFA_FCPORT_SM_HWFAIL 132 
#define  BFA_FCPORT_SM_LINKDOWN 131 
#define  BFA_FCPORT_SM_LINKUP 130 
#define  BFA_FCPORT_SM_QRESUME 129 
#define  BFA_FCPORT_SM_STOP 128 
 int /*<<< orphan*/  BFA_PORT_AEN_DISCONNECT ; 
 int /*<<< orphan*/  bfa_fcport_aen_post (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_reset_linkinfo (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_send_disable (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_sm_disabling ; 
 int /*<<< orphan*/  bfa_fcport_sm_faa_misconfig ; 
 int /*<<< orphan*/  bfa_fcport_sm_iocfail ; 
 int /*<<< orphan*/  bfa_fcport_sm_stopped ; 
 int /*<<< orphan*/  bfa_fcport_sm_toggling_qwait ; 
 int /*<<< orphan*/  bfa_reqq_wcancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_sm_disabling_qwait(struct bfa_fcport_s *fcport,
				 enum bfa_fcport_sm_event event)
{
	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_QRESUME:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		bfa_fcport_send_disable(fcport);
		break;

	case BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		bfa_reqq_wcancel(&fcport->reqq_wait);
		break;

	case BFA_FCPORT_SM_ENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_toggling_qwait);
		break;

	case BFA_FCPORT_SM_DISABLE:
		/*
		 * Already being disabled.
		 */
		break;

	case BFA_FCPORT_SM_LINKUP:
	case BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link events when doing back-to-back
		 * enable/disables.
		 */
		break;

	case BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		bfa_reqq_wcancel(&fcport->reqq_wait);
		break;

	case BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		break;

	default:
		bfa_sm_fault(fcport->bfa, event);
	}
}