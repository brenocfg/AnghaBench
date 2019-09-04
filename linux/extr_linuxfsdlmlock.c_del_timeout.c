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
struct dlm_ls {int /*<<< orphan*/  ls_timeout_mutex; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_time_list; TYPE_1__* lkb_resource; } ;
struct TYPE_2__ {struct dlm_ls* res_ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhold_lkb (struct dlm_lkb*) ; 

__attribute__((used)) static void del_timeout(struct dlm_lkb *lkb)
{
	struct dlm_ls *ls = lkb->lkb_resource->res_ls;

	mutex_lock(&ls->ls_timeout_mutex);
	if (!list_empty(&lkb->lkb_time_list)) {
		list_del_init(&lkb->lkb_time_list);
		unhold_lkb(lkb);
	}
	mutex_unlock(&ls->ls_timeout_mutex);
}