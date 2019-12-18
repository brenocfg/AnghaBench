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
struct dlm_lock {int /*<<< orphan*/  lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_print_one_lock_resource (int /*<<< orphan*/ ) ; 

void dlm_print_one_lock(struct dlm_lock *lockid)
{
	dlm_print_one_lock_resource(lockid->lockres);
}