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
typedef  size_t uint32_t ;
struct dlm_rsb {int res_master_nodeid; int res_nodeid; size_t res_hash; size_t res_bucket; int res_dir_nodeid; int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_ref; int /*<<< orphan*/  res_hashnode; scalar_t__ res_first_lkid; } ;
struct dlm_ls {TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  keep; int /*<<< orphan*/  toss; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADR ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  RSB_MASTER_UNCERTAIN ; 
 unsigned int R_RECEIVE_REQUEST ; 
 unsigned int R_REQUEST ; 
 int /*<<< orphan*/  dlm_free_rsb (struct dlm_rsb*) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_print_rsb (struct dlm_rsb*) ; 
 int dlm_search_rsb_tree (int /*<<< orphan*/ *,char*,int,struct dlm_rsb**) ; 
 int get_rsb_struct (struct dlm_ls*,char*,int,struct dlm_rsb**) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int,...) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,int,...) ; 
 int pre_rsb_struct (struct dlm_ls*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsb_clear_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int rsb_insert (struct dlm_rsb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_rsb_dir(struct dlm_ls *ls, char *name, int len,
			uint32_t hash, uint32_t b,
			int dir_nodeid, int from_nodeid,
			unsigned int flags, struct dlm_rsb **r_ret)
{
	struct dlm_rsb *r = NULL;
	int our_nodeid = dlm_our_nodeid();
	int from_local = 0;
	int from_other = 0;
	int from_dir = 0;
	int create = 0;
	int error;

	if (flags & R_RECEIVE_REQUEST) {
		if (from_nodeid == dir_nodeid)
			from_dir = 1;
		else
			from_other = 1;
	} else if (flags & R_REQUEST) {
		from_local = 1;
	}

	/*
	 * flags & R_RECEIVE_RECOVER is from dlm_recover_master_copy, so
	 * from_nodeid has sent us a lock in dlm_recover_locks, believing
	 * we're the new master.  Our local recovery may not have set
	 * res_master_nodeid to our_nodeid yet, so allow either.  Don't
	 * create the rsb; dlm_recover_process_copy() will handle EBADR
	 * by resending.
	 *
	 * If someone sends us a request, we are the dir node, and we do
	 * not find the rsb anywhere, then recreate it.  This happens if
	 * someone sends us a request after we have removed/freed an rsb
	 * from our toss list.  (They sent a request instead of lookup
	 * because they are using an rsb from their toss list.)
	 */

	if (from_local || from_dir ||
	    (from_other && (dir_nodeid == our_nodeid))) {
		create = 1;
	}

 retry:
	if (create) {
		error = pre_rsb_struct(ls);
		if (error < 0)
			goto out;
	}

	spin_lock(&ls->ls_rsbtbl[b].lock);

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	if (error)
		goto do_toss;
	
	/*
	 * rsb is active, so we can't check master_nodeid without lock_rsb.
	 */

	kref_get(&r->res_ref);
	error = 0;
	goto out_unlock;


 do_toss:
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	if (error)
		goto do_new;

	/*
	 * rsb found inactive (master_nodeid may be out of date unless
	 * we are the dir_nodeid or were the master)  No other thread
	 * is using this rsb because it's on the toss list, so we can
	 * look at or update res_master_nodeid without lock_rsb.
	 */

	if ((r->res_master_nodeid != our_nodeid) && from_other) {
		/* our rsb was not master, and another node (not the dir node)
		   has sent us a request */
		log_debug(ls, "find_rsb toss from_other %d master %d dir %d %s",
			  from_nodeid, r->res_master_nodeid, dir_nodeid,
			  r->res_name);
		error = -ENOTBLK;
		goto out_unlock;
	}

	if ((r->res_master_nodeid != our_nodeid) && from_dir) {
		/* don't think this should ever happen */
		log_error(ls, "find_rsb toss from_dir %d master %d",
			  from_nodeid, r->res_master_nodeid);
		dlm_print_rsb(r);
		/* fix it and go on */
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		rsb_clear_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = 0;
	}

	if (from_local && (r->res_master_nodeid != our_nodeid)) {
		/* Because we have held no locks on this rsb,
		   res_master_nodeid could have become stale. */
		rsb_set_flag(r, RSB_MASTER_UNCERTAIN);
		r->res_first_lkid = 0;
	}

	rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
	goto out_unlock;


 do_new:
	/*
	 * rsb not found
	 */

	if (error == -EBADR && !create)
		goto out_unlock;

	error = get_rsb_struct(ls, name, len, &r);
	if (error == -EAGAIN) {
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		goto retry;
	}
	if (error)
		goto out_unlock;

	r->res_hash = hash;
	r->res_bucket = b;
	r->res_dir_nodeid = dir_nodeid;
	kref_init(&r->res_ref);

	if (from_dir) {
		/* want to see how often this happens */
		log_debug(ls, "find_rsb new from_dir %d recreate %s",
			  from_nodeid, r->res_name);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
		goto out_add;
	}

	if (from_other && (dir_nodeid != our_nodeid)) {
		/* should never happen */
		log_error(ls, "find_rsb new from_other %d dir %d our %d %s",
			  from_nodeid, dir_nodeid, our_nodeid, r->res_name);
		dlm_free_rsb(r);
		r = NULL;
		error = -ENOTBLK;
		goto out_unlock;
	}

	if (from_other) {
		log_debug(ls, "find_rsb new from_other %d dir %d %s",
			  from_nodeid, dir_nodeid, r->res_name);
	}

	if (dir_nodeid == our_nodeid) {
		/* When we are the dir nodeid, we can set the master
		   node immediately */
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
	} else {
		/* set_master will send_lookup to dir_nodeid */
		r->res_master_nodeid = 0;
		r->res_nodeid = -1;
	}

 out_add:
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
 out_unlock:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
 out:
	*r_ret = r;
	return error;
}