#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfi_diag_dport_rsp_s {scalar_t__ status; scalar_t__ pwwn; scalar_t__ nwwn; } ;
struct TYPE_3__ {scalar_t__ status; } ;
struct TYPE_4__ {TYPE_1__ rsp; } ;
struct bfa_dport_s {scalar_t__ rp_pwwn; scalar_t__ rp_nwwn; int /*<<< orphan*/  bfa; TYPE_2__ i2hmsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DPORT_SM_FWRSP ; 
 int /*<<< orphan*/  BFA_DPORT_SM_REQFAIL ; 
 scalar_t__ BFA_STATUS_DPORT_NO_SFP ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_cb_fcdiag_dport (struct bfa_dport_s*,scalar_t__) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void
bfa_dport_req_comp(struct bfa_dport_s *dport, struct bfi_diag_dport_rsp_s *msg)
{
	msg->status = cpu_to_be32(msg->status);
	dport->i2hmsg.rsp.status = msg->status;
	dport->rp_pwwn = msg->pwwn;
	dport->rp_nwwn = msg->nwwn;

	if ((msg->status == BFA_STATUS_OK) ||
	    (msg->status == BFA_STATUS_DPORT_NO_SFP)) {
		bfa_trc(dport->bfa, msg->status);
		bfa_trc(dport->bfa, dport->rp_pwwn);
		bfa_trc(dport->bfa, dport->rp_nwwn);
		bfa_sm_send_event(dport, BFA_DPORT_SM_FWRSP);

	} else {
		bfa_trc(dport->bfa, msg->status);
		bfa_sm_send_event(dport, BFA_DPORT_SM_REQFAIL);
	}
	bfa_cb_fcdiag_dport(dport, msg->status);
}