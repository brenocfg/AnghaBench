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
struct dlm_lock_resource {int dummy; } ;
struct dlm_lock {struct dlm_lock_resource* lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_lockres_get (struct dlm_lock_resource*) ; 

void dlm_lock_attach_lockres(struct dlm_lock *lock,
			     struct dlm_lock_resource *res)
{
	dlm_lockres_get(res);
	lock->lockres = res;
}