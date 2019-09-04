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
struct bfa_fcport_s {int /*<<< orphan*/  bfa; } ;
typedef  enum bfa_fcport_sm_event { ____Placeholder_bfa_fcport_sm_event } bfa_fcport_sm_event ;

/* Variables and functions */
#define  BFA_FCPORT_SM_DISABLE 134 
#define  BFA_FCPORT_SM_DPORTDISABLE 133 
#define  BFA_FCPORT_SM_DPORTENABLE 132 
#define  BFA_FCPORT_SM_ENABLE 131 
#define  BFA_FCPORT_SM_HWFAIL 130 
#define  BFA_FCPORT_SM_START 129 
#define  BFA_FCPORT_SM_STOP 128 
 int /*<<< orphan*/  bfa_fcport_sm_disabled ; 
 int /*<<< orphan*/  bfa_fcport_sm_iocfail ; 
 int /*<<< orphan*/  bfa_fcport_sm_stopped ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_sm_dport(struct bfa_fcport_s *fcport, enum bfa_fcport_sm_event event)
{
	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_DPORTENABLE:
	case BFA_FCPORT_SM_DISABLE:
	case BFA_FCPORT_SM_ENABLE:
	case BFA_FCPORT_SM_START:
		/*
		 * Ignore event for a port that is dport
		 */
		break;

	case BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		break;

	case BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		break;

	case BFA_FCPORT_SM_DPORTDISABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		break;

	default:
		bfa_sm_fault(fcport->bfa, event);
	}
}