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
struct bfa_fcs_vport_s {int /*<<< orphan*/  lport; int /*<<< orphan*/  fdisc_retries; } ;
typedef  enum bfa_fcs_vport_event { ____Placeholder_bfa_fcs_vport_event } bfa_fcs_vport_event ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_PORT_SM_STOP ; 
#define  BFA_FCS_VPORT_SM_DELETE 131 
#define  BFA_FCS_VPORT_SM_OFFLINE 130 
#define  BFA_FCS_VPORT_SM_ONLINE 129 
#define  BFA_FCS_VPORT_SM_STOP 128 
 int /*<<< orphan*/  __vport_fcs (struct bfa_fcs_vport_s*) ; 
 int __vport_pwwn (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_vport_do_fdisc (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_vport_sm_cleanup ; 
 int /*<<< orphan*/  bfa_fcs_vport_sm_fdisc ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_vport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_vport_sm_offline(struct bfa_fcs_vport_s *vport,
			enum bfa_fcs_vport_event event)
{
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	switch (event) {
	case BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_fcs_lport_delete(&vport->lport);
		break;

	case BFA_FCS_VPORT_SM_ONLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc);
		vport->fdisc_retries = 0;
		bfa_fcs_vport_do_fdisc(vport);
		break;

	case BFA_FCS_VPORT_SM_STOP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_sm_send_event(&vport->lport, BFA_FCS_PORT_SM_STOP);
		break;

	case BFA_FCS_VPORT_SM_OFFLINE:
		/*
		 * This can happen if the vport couldn't be initialzied
		 * due the fact that the npiv was not enabled on the switch.
		 * In that case we will put the vport in offline state.
		 * However, the link can go down and cause the this event to
		 * be sent when we are already offline. Ignore it.
		 */
		break;

	default:
		bfa_sm_fault(__vport_fcs(vport), event);
	}
}