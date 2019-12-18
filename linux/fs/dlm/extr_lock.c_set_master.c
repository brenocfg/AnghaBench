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
struct dlm_rsb {scalar_t__ res_first_lkid; int res_nodeid; int res_master_nodeid; int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_dir_nodeid; int /*<<< orphan*/  res_ls; int /*<<< orphan*/  res_lookup; } ;
struct dlm_lkb {scalar_t__ lkb_id; int lkb_nodeid; int /*<<< orphan*/  lkb_rsb_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSB_MASTER_UNCERTAIN ; 
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsb_clear_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 scalar_t__ rsb_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_lookup (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  wait_pending_remove (struct dlm_rsb*) ; 

__attribute__((used)) static int set_master(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int our_nodeid = dlm_our_nodeid();

	if (rsb_flag(r, RSB_MASTER_UNCERTAIN)) {
		rsb_clear_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = lkb->lkb_id;
		lkb->lkb_nodeid = r->res_nodeid;
		return 0;
	}

	if (r->res_first_lkid && r->res_first_lkid != lkb->lkb_id) {
		list_add_tail(&lkb->lkb_rsb_lookup, &r->res_lookup);
		return 1;
	}

	if (r->res_master_nodeid == our_nodeid) {
		lkb->lkb_nodeid = 0;
		return 0;
	}

	if (r->res_master_nodeid) {
		lkb->lkb_nodeid = r->res_master_nodeid;
		return 0;
	}

	if (dlm_dir_nodeid(r) == our_nodeid) {
		/* This is a somewhat unusual case; find_rsb will usually
		   have set res_master_nodeid when dir nodeid is local, but
		   there are cases where we become the dir node after we've
		   past find_rsb and go through _request_lock again.
		   confirm_master() or process_lookup_list() needs to be
		   called after this. */
		log_debug(r->res_ls, "set_master %x self master %d dir %d %s",
			  lkb->lkb_id, r->res_master_nodeid, r->res_dir_nodeid,
			  r->res_name);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		lkb->lkb_nodeid = 0;
		return 0;
	}

	wait_pending_remove(r);

	r->res_first_lkid = lkb->lkb_id;
	send_lookup(r, lkb);
	return 1;
}