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
struct dlm_lock_resource {int /*<<< orphan*/  granted; } ;
struct TYPE_2__ {int /*<<< orphan*/  convert_type; } ;
struct dlm_lock {TYPE_1__ ml; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LKM_IVMODE ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dlm_commit_pending_cancel(struct dlm_lock_resource *res,
			       struct dlm_lock *lock)
{
	list_move_tail(&lock->list, &res->granted);
	lock->ml.convert_type = LKM_IVMODE;
}