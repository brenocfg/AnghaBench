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
struct dlm_ls {int /*<<< orphan*/  ls_lkbidr_spin; int /*<<< orphan*/  ls_lkbidr; } ;
struct dlm_lkb {int lkb_nodeid; int lkb_id; int /*<<< orphan*/  lkb_cb_work; int /*<<< orphan*/  lkb_cb_mutex; int /*<<< orphan*/  lkb_cb_list; int /*<<< orphan*/  lkb_time_list; int /*<<< orphan*/  lkb_rsb_lookup; int /*<<< orphan*/  lkb_ownqueue; int /*<<< orphan*/  lkb_ref; int /*<<< orphan*/  lkb_grmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_IV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dlm_lkb* dlm_allocate_lkb (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_callback_work ; 
 int /*<<< orphan*/  dlm_free_lkb (struct dlm_lkb*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct dlm_lkb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_lkb(struct dlm_ls *ls, struct dlm_lkb **lkb_ret)
{
	struct dlm_lkb *lkb;
	int rv;

	lkb = dlm_allocate_lkb(ls);
	if (!lkb)
		return -ENOMEM;

	lkb->lkb_nodeid = -1;
	lkb->lkb_grmode = DLM_LOCK_IV;
	kref_init(&lkb->lkb_ref);
	INIT_LIST_HEAD(&lkb->lkb_ownqueue);
	INIT_LIST_HEAD(&lkb->lkb_rsb_lookup);
	INIT_LIST_HEAD(&lkb->lkb_time_list);
	INIT_LIST_HEAD(&lkb->lkb_cb_list);
	mutex_init(&lkb->lkb_cb_mutex);
	INIT_WORK(&lkb->lkb_cb_work, dlm_callback_work);

	idr_preload(GFP_NOFS);
	spin_lock(&ls->ls_lkbidr_spin);
	rv = idr_alloc(&ls->ls_lkbidr, lkb, 1, 0, GFP_NOWAIT);
	if (rv >= 0)
		lkb->lkb_id = rv;
	spin_unlock(&ls->ls_lkbidr_spin);
	idr_preload_end();

	if (rv < 0) {
		log_error(ls, "create_lkb idr error %d", rv);
		dlm_free_lkb(lkb);
		return rv;
	}

	*lkb_ret = lkb;
	return 0;
}