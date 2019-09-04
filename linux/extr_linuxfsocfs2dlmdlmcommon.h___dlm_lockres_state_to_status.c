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
struct dlm_lock_resource {int state; int /*<<< orphan*/  spinlock; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int DLM_FORWARD ; 
 int DLM_LOCK_RES_IN_PROGRESS ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int DLM_LOCK_RES_RECOVERING ; 
 int DLM_LOCK_RES_RECOVERY_WAITING ; 
 int DLM_MIGRATING ; 
 int DLM_NORMAL ; 
 int DLM_RECOVERING ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline enum dlm_status
__dlm_lockres_state_to_status(struct dlm_lock_resource *res)
{
	enum dlm_status status = DLM_NORMAL;

	assert_spin_locked(&res->spinlock);

	if (res->state & (DLM_LOCK_RES_RECOVERING|
			DLM_LOCK_RES_RECOVERY_WAITING))
		status = DLM_RECOVERING;
	else if (res->state & DLM_LOCK_RES_MIGRATING)
		status = DLM_MIGRATING;
	else if (res->state & DLM_LOCK_RES_IN_PROGRESS)
		status = DLM_FORWARD;

	return status;
}