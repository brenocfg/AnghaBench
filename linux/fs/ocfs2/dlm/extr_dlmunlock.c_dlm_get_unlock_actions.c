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
struct dlm_lockstatus {int dummy; } ;
struct dlm_lock_resource {int /*<<< orphan*/  granted; } ;
struct dlm_lock {int dummy; } ;
struct dlm_ctxt {int dummy; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int DLM_DENIED ; 
 int DLM_NORMAL ; 
 int DLM_UNLOCK_CALL_AST ; 
 int DLM_UNLOCK_FREE_LOCK ; 
 int DLM_UNLOCK_REMOVE_LOCK ; 
 int /*<<< orphan*/  dlm_error (int) ; 
 int /*<<< orphan*/  dlm_lock_on_list (int /*<<< orphan*/ *,struct dlm_lock*) ; 

__attribute__((used)) static enum dlm_status dlm_get_unlock_actions(struct dlm_ctxt *dlm,
					      struct dlm_lock_resource *res,
					      struct dlm_lock *lock,
					      struct dlm_lockstatus *lksb,
					      int *actions)
{
	enum dlm_status status;

	/* unlock request */
	if (!dlm_lock_on_list(&res->granted, lock)) {
		status = DLM_DENIED;
		dlm_error(status);
		*actions = 0;
	} else {
		/* unlock granted lock */
		status = DLM_NORMAL;
		*actions = (DLM_UNLOCK_FREE_LOCK |
			    DLM_UNLOCK_CALL_AST |
			    DLM_UNLOCK_REMOVE_LOCK);
	}
	return status;
}