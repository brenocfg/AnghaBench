#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dlm_lock_resource {int /*<<< orphan*/  granted; } ;
struct TYPE_3__ {int /*<<< orphan*/  convert_type; } ;
struct dlm_lock {TYPE_2__* lksb; TYPE_1__ ml; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int DLM_LKSB_GET_LVB ; 
 int DLM_LKSB_PUT_LVB ; 
 int /*<<< orphan*/  LKM_IVMODE ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dlm_revert_pending_convert(struct dlm_lock_resource *res,
				struct dlm_lock *lock)
{
	/* do not alter lock refcount.  switching lists. */
	list_move_tail(&lock->list, &res->granted);
	lock->ml.convert_type = LKM_IVMODE;
	lock->lksb->flags &= ~(DLM_LKSB_GET_LVB|DLM_LKSB_PUT_LVB);
}