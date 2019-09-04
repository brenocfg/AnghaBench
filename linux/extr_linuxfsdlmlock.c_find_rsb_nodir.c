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
struct dlm_rsb {int res_master_nodeid; int res_nodeid; size_t res_hash; size_t res_bucket; int res_dir_nodeid; int /*<<< orphan*/  res_ref; int /*<<< orphan*/  res_hashnode; } ;
struct dlm_ls {TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  keep; int /*<<< orphan*/  toss; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTBLK ; 
 unsigned int R_RECEIVE_RECOVER ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_print_rsb (struct dlm_rsb*) ; 
 int dlm_search_rsb_tree (int /*<<< orphan*/ *,char*,int,struct dlm_rsb**) ; 
 int get_rsb_struct (struct dlm_ls*,char*,int,struct dlm_rsb**) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,int,int) ; 
 int pre_rsb_struct (struct dlm_ls*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rsb_insert (struct dlm_rsb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_rsb_nodir(struct dlm_ls *ls, char *name, int len,
			  uint32_t hash, uint32_t b,
			  int dir_nodeid, int from_nodeid,
			  unsigned int flags, struct dlm_rsb **r_ret)
{
	struct dlm_rsb *r = NULL;
	int our_nodeid = dlm_our_nodeid();
	int recover = (flags & R_RECEIVE_RECOVER);
	int error;

 retry:
	error = pre_rsb_struct(ls);
	if (error < 0)
		goto out;

	spin_lock(&ls->ls_rsbtbl[b].lock);

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	if (error)
		goto do_toss;

	/*
	 * rsb is active, so we can't check master_nodeid without lock_rsb.
	 */

	kref_get(&r->res_ref);
	goto out_unlock;


 do_toss:
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	if (error)
		goto do_new;

	/*
	 * rsb found inactive. No other thread is using this rsb because
	 * it's on the toss list, so we can look at or update
	 * res_master_nodeid without lock_rsb.
	 */

	if (!recover && (r->res_master_nodeid != our_nodeid) && from_nodeid) {
		/* our rsb is not master, and another node has sent us a
		   request; this should never happen */
		log_error(ls, "find_rsb toss from_nodeid %d master %d dir %d",
			  from_nodeid, r->res_master_nodeid, dir_nodeid);
		dlm_print_rsb(r);
		error = -ENOTBLK;
		goto out_unlock;
	}

	if (!recover && (r->res_master_nodeid != our_nodeid) &&
	    (dir_nodeid == our_nodeid)) {
		/* our rsb is not master, and we are dir; may as well fix it;
		   this should never happen */
		log_error(ls, "find_rsb toss our %d master %d dir %d",
			  our_nodeid, r->res_master_nodeid, dir_nodeid);
		dlm_print_rsb(r);
		r->res_master_nodeid = our_nodeid;
		r->res_nodeid = 0;
	}

	rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
	goto out_unlock;


 do_new:
	/*
	 * rsb not found
	 */

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
	r->res_master_nodeid = dir_nodeid;
	r->res_nodeid = (dir_nodeid == our_nodeid) ? 0 : dir_nodeid;
	kref_init(&r->res_ref);

	error = rsb_insert(r, &ls->ls_rsbtbl[b].keep);
 out_unlock:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
 out:
	*r_ret = r;
	return error;
}