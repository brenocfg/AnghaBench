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
typedef  int uint32_t ;
struct dlm_rsb {int res_master_nodeid; int /*<<< orphan*/  res_hashnode; int /*<<< orphan*/  res_ref; int /*<<< orphan*/  res_first_lkid; } ;
struct TYPE_3__ {int h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_extra; int /*<<< orphan*/  m_hash; TYPE_1__ m_header; } ;
struct dlm_ls {int ls_rsbtbl_size; TYPE_2__* ls_rsbtbl; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  toss; int /*<<< orphan*/  keep; } ;

/* Variables and functions */
 int DLM_RESNAME_MAXLEN ; 
 int /*<<< orphan*/  dlm_free_rsb (struct dlm_rsb*) ; 
 int dlm_hash2nodeid (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_print_rsb (struct dlm_rsb*) ; 
 int dlm_search_rsb_tree (int /*<<< orphan*/ *,char*,int,struct dlm_rsb**) ; 
 int jhash (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_rsb ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int receive_extralen (struct dlm_message*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void receive_remove(struct dlm_ls *ls, struct dlm_message *ms)
{
	char name[DLM_RESNAME_MAXLEN+1];
	struct dlm_rsb *r;
	uint32_t hash, b;
	int rv, len, dir_nodeid, from_nodeid;

	from_nodeid = ms->m_header.h_nodeid;

	len = receive_extralen(ms);

	if (len > DLM_RESNAME_MAXLEN) {
		log_error(ls, "receive_remove from %d bad len %d",
			  from_nodeid, len);
		return;
	}

	dir_nodeid = dlm_hash2nodeid(ls, ms->m_hash);
	if (dir_nodeid != dlm_our_nodeid()) {
		log_error(ls, "receive_remove from %d bad nodeid %d",
			  from_nodeid, dir_nodeid);
		return;
	}

	/* Look for name on rsbtbl.toss, if it's there, kill it.
	   If it's on rsbtbl.keep, it's being used, and we should ignore this
	   message.  This is an expected race between the dir node sending a
	   request to the master node at the same time as the master node sends
	   a remove to the dir node.  The resolution to that race is for the
	   dir node to ignore the remove message, and the master node to
	   recreate the master rsb when it gets a request from the dir node for
	   an rsb it doesn't have. */

	memset(name, 0, sizeof(name));
	memcpy(name, ms->m_extra, len);

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[b].lock);

	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	if (rv) {
		/* verify the rsb is on keep list per comment above */
		rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
		if (rv) {
			/* should not happen */
			log_error(ls, "receive_remove from %d not found %s",
				  from_nodeid, name);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			return;
		}
		if (r->res_master_nodeid != from_nodeid) {
			/* should not happen */
			log_error(ls, "receive_remove keep from %d master %d",
				  from_nodeid, r->res_master_nodeid);
			dlm_print_rsb(r);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			return;
		}

		log_debug(ls, "receive_remove from %d master %d first %x %s",
			  from_nodeid, r->res_master_nodeid, r->res_first_lkid,
			  name);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		return;
	}

	if (r->res_master_nodeid != from_nodeid) {
		log_error(ls, "receive_remove toss from %d master %d",
			  from_nodeid, r->res_master_nodeid);
		dlm_print_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		return;
	}

	if (kref_put(&r->res_ref, kill_rsb)) {
		rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		dlm_free_rsb(r);
	} else {
		log_error(ls, "receive_remove from %d rsb ref error",
			  from_nodeid);
		dlm_print_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
	}
}