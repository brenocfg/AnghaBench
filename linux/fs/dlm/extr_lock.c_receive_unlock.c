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
struct dlm_rsb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {scalar_t__ m_lkid; TYPE_1__ m_header; int /*<<< orphan*/  m_remid; } ;
struct dlm_lkb {scalar_t__ lkb_remid; struct dlm_rsb* lkb_resource; int /*<<< orphan*/  lkb_id; } ;
struct dlm_ls {struct dlm_lkb ls_stub_lkb; struct dlm_rsb ls_stub_rsb; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int do_unlock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  do_unlock_effects (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int find_lkb (struct dlm_ls*,int /*<<< orphan*/ ,struct dlm_lkb**) ; 
 int /*<<< orphan*/  hold_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  receive_flags (struct dlm_lkb*,struct dlm_message*) ; 
 int receive_unlock_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  send_unlock_reply (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int /*<<< orphan*/  setup_stub_lkb (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 
 int validate_message (struct dlm_lkb*,struct dlm_message*) ; 

__attribute__((used)) static int receive_unlock(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	struct dlm_rsb *r;
	int error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	if (error)
		goto fail;

	if (lkb->lkb_remid != ms->m_lkid) {
		log_error(ls, "receive_unlock %x remid %x remote %d %x",
			  lkb->lkb_id, lkb->lkb_remid,
			  ms->m_header.h_nodeid, ms->m_lkid);
		error = -ENOENT;
		dlm_put_lkb(lkb);
		goto fail;
	}

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	if (error)
		goto out;

	receive_flags(lkb, ms);

	error = receive_unlock_args(ls, lkb, ms);
	if (error) {
		send_unlock_reply(r, lkb, error);
		goto out;
	}

	error = do_unlock(r, lkb);
	send_unlock_reply(r, lkb, error);
	do_unlock_effects(r, lkb, error);
 out:
	unlock_rsb(r);
	put_rsb(r);
	dlm_put_lkb(lkb);
	return 0;

 fail:
	setup_stub_lkb(ls, ms);
	send_unlock_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	return error;
}