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
struct TYPE_2__ {int /*<<< orphan*/  fab_no_npiv; } ;
struct bfa_fcs_vport_s {int /*<<< orphan*/  lport; TYPE_1__ vport_stats; } ;
typedef  enum bfa_fcs_vport_event { ____Placeholder_bfa_fcs_vport_event } bfa_fcs_vport_event ;

/* Variables and functions */
#define  BFA_FCS_VPORT_SM_DELETE 131 
#define  BFA_FCS_VPORT_SM_OFFLINE 130 
#define  BFA_FCS_VPORT_SM_ONLINE 129 
#define  BFA_FCS_VPORT_SM_START 128 
 int /*<<< orphan*/  __vport_fabric (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  __vport_fcs (struct bfa_fcs_vport_s*) ; 
 int __vport_pwwn (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_npiv_capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_lport_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_vport_do_fdisc (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_vport_sm_cleanup ; 
 int /*<<< orphan*/  bfa_fcs_vport_sm_fdisc ; 
 int /*<<< orphan*/  bfa_fcs_vport_sm_offline ; 
 int /*<<< orphan*/  bfa_sm_cmp_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_vport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_vport_sm_created(struct bfa_fcs_vport_s *vport,
			enum bfa_fcs_vport_event event)
{
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	switch (event) {
	case BFA_FCS_VPORT_SM_START:
		if (bfa_sm_cmp_state(__vport_fabric(vport),
					bfa_fcs_fabric_sm_online)
		    && bfa_fcs_fabric_npiv_capable(__vport_fabric(vport))) {
			bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc);
			bfa_fcs_vport_do_fdisc(vport);
		} else {
			/*
			 * Fabric is offline or not NPIV capable, stay in
			 * offline state.
			 */
			vport->vport_stats.fab_no_npiv++;
			bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		}
		break;

	case BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_fcs_lport_delete(&vport->lport);
		break;

	case BFA_FCS_VPORT_SM_ONLINE:
	case BFA_FCS_VPORT_SM_OFFLINE:
		/*
		 * Ignore ONLINE/OFFLINE events from fabric
		 * till vport is started.
		 */
		break;

	default:
		bfa_sm_fault(__vport_fcs(vport), event);
	}
}