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
struct dlm_rsb {scalar_t__ res_master_nodeid; } ;
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_extra; int /*<<< orphan*/  m_lkid; TYPE_1__ m_header; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_flags; } ;
struct dlm_ls {struct dlm_lkb ls_stub_lkb; struct dlm_rsb ls_stub_rsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_IFL_MSTCPY ; 
 int EBADR ; 
 int EINPROGRESS ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  R_RECEIVE_REQUEST ; 
 int /*<<< orphan*/  __put_lkb (struct dlm_ls*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  attach_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 int create_lkb (struct dlm_ls*,struct dlm_lkb**) ; 
 scalar_t__ dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int do_request (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  do_request_effects (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int find_rsb (struct dlm_ls*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_limit (struct dlm_ls*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int receive_extralen (struct dlm_message*) ; 
 int /*<<< orphan*/  receive_flags (struct dlm_lkb*,struct dlm_message*) ; 
 int receive_request_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  send_repeat_remove (struct dlm_ls*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_request_reply (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int /*<<< orphan*/  setup_stub_lkb (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 
 int validate_master_nodeid (struct dlm_ls*,struct dlm_rsb*,int) ; 

__attribute__((used)) static int receive_request(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	struct dlm_rsb *r;
	int from_nodeid;
	int error, namelen = 0;

	from_nodeid = ms->m_header.h_nodeid;

	error = create_lkb(ls, &lkb);
	if (error)
		goto fail;

	receive_flags(lkb, ms);
	lkb->lkb_flags |= DLM_IFL_MSTCPY;
	error = receive_request_args(ls, lkb, ms);
	if (error) {
		__put_lkb(ls, lkb);
		goto fail;
	}

	/* The dir node is the authority on whether we are the master
	   for this rsb or not, so if the master sends us a request, we should
	   recreate the rsb if we've destroyed it.   This race happens when we
	   send a remove message to the dir node at the same time that the dir
	   node sends us a request for the rsb. */

	namelen = receive_extralen(ms);

	error = find_rsb(ls, ms->m_extra, namelen, from_nodeid,
			 R_RECEIVE_REQUEST, &r);
	if (error) {
		__put_lkb(ls, lkb);
		goto fail;
	}

	lock_rsb(r);

	if (r->res_master_nodeid != dlm_our_nodeid()) {
		error = validate_master_nodeid(ls, r, from_nodeid);
		if (error) {
			unlock_rsb(r);
			put_rsb(r);
			__put_lkb(ls, lkb);
			goto fail;
		}
	}

	attach_lkb(r, lkb);
	error = do_request(r, lkb);
	send_request_reply(r, lkb, error);
	do_request_effects(r, lkb, error);

	unlock_rsb(r);
	put_rsb(r);

	if (error == -EINPROGRESS)
		error = 0;
	if (error)
		dlm_put_lkb(lkb);
	return 0;

 fail:
	/* TODO: instead of returning ENOTBLK, add the lkb to res_lookup
	   and do this receive_request again from process_lookup_list once
	   we get the lookup reply.  This would avoid a many repeated
	   ENOTBLK request failures when the lookup reply designating us
	   as master is delayed. */

	/* We could repeatedly return -EBADR here if our send_remove() is
	   delayed in being sent/arriving/being processed on the dir node.
	   Another node would repeatedly lookup up the master, and the dir
	   node would continue returning our nodeid until our send_remove
	   took effect.

	   We send another remove message in case our previous send_remove
	   was lost/ignored/missed somehow. */

	if (error != -ENOTBLK) {
		log_limit(ls, "receive_request %x from %d %d",
			  ms->m_lkid, from_nodeid, error);
	}

	if (namelen && error == -EBADR) {
		send_repeat_remove(ls, ms->m_extra, namelen);
		msleep(1000);
	}

	setup_stub_lkb(ls, ms);
	send_request_reply(&ls->ls_stub_rsb, &ls->ls_stub_lkb, error);
	return error;
}