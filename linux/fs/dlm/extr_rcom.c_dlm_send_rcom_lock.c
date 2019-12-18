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
struct rcom_lock {int dummy; } ;
struct dlm_rsb {int /*<<< orphan*/  res_nodeid; struct dlm_ls* res_ls; } ;
struct dlm_rcom {unsigned long rc_id; scalar_t__ rc_buf; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {scalar_t__ ls_lvblen; } ;
struct dlm_lkb {scalar_t__ lkb_lvbptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_LOCK ; 
 int create_rcom (struct dlm_ls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  pack_rcom_lock (struct dlm_rsb*,struct dlm_lkb*,struct rcom_lock*) ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

int dlm_send_rcom_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	struct dlm_ls *ls = r->res_ls;
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	struct rcom_lock *rl;
	int error, len = sizeof(struct rcom_lock);

	if (lkb->lkb_lvbptr)
		len += ls->ls_lvblen;

	error = create_rcom(ls, r->res_nodeid, DLM_RCOM_LOCK, len, &rc, &mh);
	if (error)
		goto out;

	rl = (struct rcom_lock *) rc->rc_buf;
	pack_rcom_lock(r, lkb, rl);
	rc->rc_id = (unsigned long) r;

	send_rcom(ls, mh, rc);
 out:
	return error;
}