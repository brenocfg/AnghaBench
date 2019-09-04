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
struct dlm_ls {int /*<<< orphan*/  ls_orphans_mutex; int /*<<< orphan*/  ls_orphans; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_ua; int /*<<< orphan*/  lkb_ownqueue; } ;
struct dlm_args {int dummy; } ;

/* Variables and functions */
 int DLM_ECANCEL ; 
 int cancel_lock (struct dlm_ls*,struct dlm_lkb*,struct dlm_args*) ; 
 int /*<<< orphan*/  hold_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_unlock_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_args*) ; 

__attribute__((used)) static int orphan_proc_lock(struct dlm_ls *ls, struct dlm_lkb *lkb)
{
	struct dlm_args args;
	int error;

	hold_lkb(lkb); /* reference for the ls_orphans list */
	mutex_lock(&ls->ls_orphans_mutex);
	list_add_tail(&lkb->lkb_ownqueue, &ls->ls_orphans);
	mutex_unlock(&ls->ls_orphans_mutex);

	set_unlock_args(0, lkb->lkb_ua, &args);

	error = cancel_lock(ls, lkb, &args);
	if (error == -DLM_ECANCEL)
		error = 0;
	return error;
}