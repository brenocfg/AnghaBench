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
struct dlm_rsb {scalar_t__ res_id; struct dlm_ls* res_ls; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recover_idr_lock; int /*<<< orphan*/  ls_recover_list_count; int /*<<< orphan*/  ls_recover_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recover_idr_del(struct dlm_rsb *r)
{
	struct dlm_ls *ls = r->res_ls;

	spin_lock(&ls->ls_recover_idr_lock);
	idr_remove(&ls->ls_recover_idr, r->res_id);
	r->res_id = 0;
	ls->ls_recover_list_count--;
	spin_unlock(&ls->ls_recover_idr_lock);

	dlm_put_rsb(r);
}