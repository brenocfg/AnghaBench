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
struct dlm_lock_resource {int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_SETREF_INPROG ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dlm_assert_master_post_handler(int status, void *data, void *ret_data)
{
	struct dlm_lock_resource *res = (struct dlm_lock_resource *)ret_data;

	if (ret_data) {
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_SETREF_INPROG;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
		dlm_lockres_put(res);
	}
	return;
}