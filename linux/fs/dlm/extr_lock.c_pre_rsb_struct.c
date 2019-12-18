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
struct dlm_rsb {int /*<<< orphan*/  res_hashchain; } ;
struct dlm_ls {int ls_new_rsb_count; int /*<<< orphan*/  ls_new_rsb_spin; int /*<<< orphan*/  ls_new_rsb; } ;
struct TYPE_2__ {int ci_new_rsb_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dlm_rsb* dlm_allocate_rsb (struct dlm_ls*) ; 
 TYPE_1__ dlm_config ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pre_rsb_struct(struct dlm_ls *ls)
{
	struct dlm_rsb *r1, *r2;
	int count = 0;

	spin_lock(&ls->ls_new_rsb_spin);
	if (ls->ls_new_rsb_count > dlm_config.ci_new_rsb_count / 2) {
		spin_unlock(&ls->ls_new_rsb_spin);
		return 0;
	}
	spin_unlock(&ls->ls_new_rsb_spin);

	r1 = dlm_allocate_rsb(ls);
	r2 = dlm_allocate_rsb(ls);

	spin_lock(&ls->ls_new_rsb_spin);
	if (r1) {
		list_add(&r1->res_hashchain, &ls->ls_new_rsb);
		ls->ls_new_rsb_count++;
	}
	if (r2) {
		list_add(&r2->res_hashchain, &ls->ls_new_rsb);
		ls->ls_new_rsb_count++;
	}
	count = ls->ls_new_rsb_count;
	spin_unlock(&ls->ls_new_rsb_spin);

	if (!count)
		return -ENOMEM;
	return 0;
}