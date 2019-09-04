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
struct dlm_rsb {int res_id; struct dlm_ls* res_ls; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recover_idr_lock; int /*<<< orphan*/  ls_recover_list_count; int /*<<< orphan*/  ls_recover_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dlm_hold_rsb (struct dlm_rsb*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct dlm_rsb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int recover_idr_add(struct dlm_rsb *r)
{
	struct dlm_ls *ls = r->res_ls;
	int rv;

	idr_preload(GFP_NOFS);
	spin_lock(&ls->ls_recover_idr_lock);
	if (r->res_id) {
		rv = -1;
		goto out_unlock;
	}
	rv = idr_alloc(&ls->ls_recover_idr, r, 1, 0, GFP_NOWAIT);
	if (rv < 0)
		goto out_unlock;

	r->res_id = rv;
	ls->ls_recover_list_count++;
	dlm_hold_rsb(r);
	rv = 0;
out_unlock:
	spin_unlock(&ls->ls_recover_idr_lock);
	idr_preload_end();
	return rv;
}