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
typedef  int /*<<< orphan*/  uint32_t ;
struct rcom_lock {void* rl_result; void* rl_remid; int /*<<< orphan*/  rl_status; int /*<<< orphan*/  rl_namelen; int /*<<< orphan*/  rl_name; int /*<<< orphan*/  rl_lkid; scalar_t__ rl_parent_lkid; } ;
struct dlm_rsb {int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_waitqueue; } ;
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_rcom {TYPE_1__ rc_header; scalar_t__ rc_buf; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recover_seq; int /*<<< orphan*/  ls_recover_locks_in; } ;
struct dlm_lkb {int lkb_id; int /*<<< orphan*/  lkb_recover_seq; } ;

/* Variables and functions */
 int EBADR ; 
 int EEXIST ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RSB_RECOVER_GRANT ; 
 int /*<<< orphan*/  R_RECEIVE_RECOVER ; 
 int /*<<< orphan*/  __put_lkb (struct dlm_ls*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 void* cpu_to_le32 (int) ; 
 int create_lkb (struct dlm_ls*,struct dlm_lkb**) ; 
 scalar_t__ dlm_dir_nodeid (struct dlm_rsb*) ; 
 scalar_t__ dlm_no_directory (struct dlm_ls*) ; 
 scalar_t__ dlm_our_nodeid () ; 
 int find_rsb (struct dlm_ls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_rinfo (struct dlm_ls*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int receive_rcom_lock_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_rsb*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 struct dlm_lkb* search_remid (struct dlm_rsb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

int dlm_recover_master_copy(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	struct rcom_lock *rl = (struct rcom_lock *) rc->rc_buf;
	struct dlm_rsb *r;
	struct dlm_lkb *lkb;
	uint32_t remid = 0;
	int from_nodeid = rc->rc_header.h_nodeid;
	int error;

	if (rl->rl_parent_lkid) {
		error = -EOPNOTSUPP;
		goto out;
	}

	remid = le32_to_cpu(rl->rl_lkid);

	/* In general we expect the rsb returned to be R_MASTER, but we don't
	   have to require it.  Recovery of masters on one node can overlap
	   recovery of locks on another node, so one node can send us MSTCPY
	   locks before we've made ourselves master of this rsb.  We can still
	   add new MSTCPY locks that we receive here without any harm; when
	   we make ourselves master, dlm_recover_masters() won't touch the
	   MSTCPY locks we've received early. */

	error = find_rsb(ls, rl->rl_name, le16_to_cpu(rl->rl_namelen),
			 from_nodeid, R_RECEIVE_RECOVER, &r);
	if (error)
		goto out;

	lock_rsb(r);

	if (dlm_no_directory(ls) && (dlm_dir_nodeid(r) != dlm_our_nodeid())) {
		log_error(ls, "dlm_recover_master_copy remote %d %x not dir",
			  from_nodeid, remid);
		error = -EBADR;
		goto out_unlock;
	}

	lkb = search_remid(r, from_nodeid, remid);
	if (lkb) {
		error = -EEXIST;
		goto out_remid;
	}

	error = create_lkb(ls, &lkb);
	if (error)
		goto out_unlock;

	error = receive_rcom_lock_args(ls, lkb, r, rc);
	if (error) {
		__put_lkb(ls, lkb);
		goto out_unlock;
	}

	attach_lkb(r, lkb);
	add_lkb(r, lkb, rl->rl_status);
	error = 0;
	ls->ls_recover_locks_in++;

	if (!list_empty(&r->res_waitqueue) || !list_empty(&r->res_convertqueue))
		rsb_set_flag(r, RSB_RECOVER_GRANT);

 out_remid:
	/* this is the new value returned to the lock holder for
	   saving in its process-copy lkb */
	rl->rl_remid = cpu_to_le32(lkb->lkb_id);

	lkb->lkb_recover_seq = ls->ls_recover_seq;

 out_unlock:
	unlock_rsb(r);
	put_rsb(r);
 out:
	if (error && error != -EEXIST)
		log_rinfo(ls, "dlm_recover_master_copy remote %d %x error %d",
			  from_nodeid, remid, error);
	rl->rl_result = cpu_to_le32(error);
	return error;
}