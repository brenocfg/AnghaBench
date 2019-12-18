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
struct dlm_lock_resource {int dummy; } ;
struct dlm_lock {TYPE_1__* lksb; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKSB_GET_LVB ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void dlm_revert_pending_lock(struct dlm_lock_resource *res,
			     struct dlm_lock *lock)
{
	/* remove from local queue if it failed */
	list_del_init(&lock->list);
	lock->lksb->flags &= ~DLM_LKSB_GET_LVB;
}