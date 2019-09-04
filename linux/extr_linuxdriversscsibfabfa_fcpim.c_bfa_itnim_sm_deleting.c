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
struct bfa_itnim_s {int /*<<< orphan*/  bfa; TYPE_1__* rport; } ;
typedef  enum bfa_itnim_event { ____Placeholder_bfa_itnim_event } bfa_itnim_event ;
struct TYPE_2__ {int rport_tag; } ;

/* Variables and functions */
#define  BFA_ITNIM_SM_FWRSP 129 
#define  BFA_ITNIM_SM_HWFAIL 128 
 int /*<<< orphan*/  bfa_fcpim_delitn (struct bfa_itnim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_itnim_sm_deleting(struct bfa_itnim_s *itnim, enum bfa_itnim_event event)
{
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	switch (event) {
	case BFA_ITNIM_SM_FWRSP:
	case BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_fcpim_delitn(itnim);
		break;

	default:
		bfa_sm_fault(itnim->bfa, event);
	}
}