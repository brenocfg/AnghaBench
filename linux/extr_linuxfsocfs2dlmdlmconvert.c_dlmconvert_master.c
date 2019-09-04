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
struct dlm_lock {int dummy; } ;
struct dlm_ctxt {int dummy; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_IN_PROGRESS ; 
 int DLM_NORMAL ; 
 int DLM_NOTQUEUED ; 
 int /*<<< orphan*/  __dlm_lockres_reserve_ast (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres (struct dlm_lock_resource*) ; 
 int __dlmconvert_master (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_lock*,int,int,int*,int*) ; 
 int /*<<< orphan*/  dlm_error (int) ; 
 int /*<<< orphan*/  dlm_kick_thread (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_release_ast (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_queue_ast (struct dlm_ctxt*,struct dlm_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

enum dlm_status dlmconvert_master(struct dlm_ctxt *dlm,
				  struct dlm_lock_resource *res,
				  struct dlm_lock *lock, int flags, int type)
{
	int call_ast = 0, kick_thread = 0;
	enum dlm_status status;

	spin_lock(&res->spinlock);
	/* we are not in a network handler, this is fine */
	__dlm_wait_on_lockres(res);
	__dlm_lockres_reserve_ast(res);
	res->state |= DLM_LOCK_RES_IN_PROGRESS;

	status = __dlmconvert_master(dlm, res, lock, flags, type,
				     &call_ast, &kick_thread);

	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);
	if (status != DLM_NORMAL && status != DLM_NOTQUEUED)
		dlm_error(status);

	/* either queue the ast or release it */
	if (call_ast)
		dlm_queue_ast(dlm, lock);
	else
		dlm_lockres_release_ast(dlm, res);

	if (kick_thread)
		dlm_kick_thread(dlm, res);

	return status;
}