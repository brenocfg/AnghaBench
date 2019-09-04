#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union bfi_itn_i2h_msg_u {TYPE_3__* sler_event; TYPE_2__* delete_rsp; TYPE_1__* create_rsp; struct bfi_msg_s* msg; } ;
struct TYPE_8__ {int msg_id; } ;
struct bfi_msg_s {TYPE_4__ mhdr; } ;
struct bfa_s {int dummy; } ;
struct bfa_itnim_s {int dummy; } ;
struct bfa_fcpim_s {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  bfa_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; int /*<<< orphan*/  bfa_handle; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  bfa_handle; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 struct bfa_itnim_s* BFA_ITNIM_FROM_TAG (struct bfa_fcpim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFA_ITNIM_SM_FWRSP ; 
 int /*<<< orphan*/  BFA_ITNIM_SM_SLER ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  BFI_ITN_I2H_CREATE_RSP 130 
#define  BFI_ITN_I2H_DELETE_RSP 129 
#define  BFI_ITN_I2H_SLER_EVENT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  create_comps ; 
 int /*<<< orphan*/  delete_comps ; 
 int /*<<< orphan*/  sler_events ; 

void
bfa_itnim_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	union bfi_itn_i2h_msg_u msg;
	struct bfa_itnim_s *itnim;

	bfa_trc(bfa, m->mhdr.msg_id);

	msg.msg = m;

	switch (m->mhdr.msg_id) {
	case BFI_ITN_I2H_CREATE_RSP:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.create_rsp->bfa_handle);
		WARN_ON(msg.create_rsp->status != BFA_STATUS_OK);
		bfa_stats(itnim, create_comps);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_FWRSP);
		break;

	case BFI_ITN_I2H_DELETE_RSP:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.delete_rsp->bfa_handle);
		WARN_ON(msg.delete_rsp->status != BFA_STATUS_OK);
		bfa_stats(itnim, delete_comps);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_FWRSP);
		break;

	case BFI_ITN_I2H_SLER_EVENT:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.sler_event->bfa_handle);
		bfa_stats(itnim, sler_events);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_SLER);
		break;

	default:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	}
}