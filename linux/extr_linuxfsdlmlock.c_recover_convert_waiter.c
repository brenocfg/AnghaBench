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
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {TYPE_1__ m_header; int /*<<< orphan*/  m_result; int /*<<< orphan*/  m_type; int /*<<< orphan*/  m_flags; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {scalar_t__ lkb_grmode; scalar_t__ lkb_rqmode; int /*<<< orphan*/  lkb_flags; int /*<<< orphan*/  lkb_resource; int /*<<< orphan*/  lkb_nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_IFL_RESEND ; 
 int /*<<< orphan*/  DLM_IFL_STUB_MS ; 
 scalar_t__ DLM_LOCK_IV ; 
 int /*<<< orphan*/  DLM_MSG_CONVERT_REPLY ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  RSB_RECOVER_CONVERT ; 
 int /*<<< orphan*/  _receive_convert_reply (struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  hold_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  memset (struct dlm_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ middle_conversion (struct dlm_lkb*) ; 
 int /*<<< orphan*/  rsb_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhold_lkb (struct dlm_lkb*) ; 

__attribute__((used)) static void recover_convert_waiter(struct dlm_ls *ls, struct dlm_lkb *lkb,
				   struct dlm_message *ms_stub)
{
	if (middle_conversion(lkb)) {
		hold_lkb(lkb);
		memset(ms_stub, 0, sizeof(struct dlm_message));
		ms_stub->m_flags = DLM_IFL_STUB_MS;
		ms_stub->m_type = DLM_MSG_CONVERT_REPLY;
		ms_stub->m_result = -EINPROGRESS;
		ms_stub->m_header.h_nodeid = lkb->lkb_nodeid;
		_receive_convert_reply(lkb, ms_stub);

		/* Same special case as in receive_rcom_lock_args() */
		lkb->lkb_grmode = DLM_LOCK_IV;
		rsb_set_flag(lkb->lkb_resource, RSB_RECOVER_CONVERT);
		unhold_lkb(lkb);

	} else if (lkb->lkb_rqmode >= lkb->lkb_grmode) {
		lkb->lkb_flags |= DLM_IFL_RESEND;
	}

	/* lkb->lkb_rqmode < lkb->lkb_grmode shouldn't happen since down
	   conversions are async; there's no reply from the remote master */
}