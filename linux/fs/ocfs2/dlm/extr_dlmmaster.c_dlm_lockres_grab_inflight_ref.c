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
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_lockres_grab_inflight_ref (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

void dlm_lockres_grab_inflight_ref(struct dlm_ctxt *dlm,
				   struct dlm_lock_resource *res)
{
	assert_spin_locked(&res->spinlock);
	__dlm_lockres_grab_inflight_ref(dlm, res);
}