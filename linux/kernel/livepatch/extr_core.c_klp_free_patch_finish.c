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
struct klp_patch {int /*<<< orphan*/  mod; int /*<<< orphan*/  forced; int /*<<< orphan*/  finish; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void klp_free_patch_finish(struct klp_patch *patch)
{
	/*
	 * Avoid deadlock with enabled_store() sysfs callback by
	 * calling this outside klp_mutex. It is safe because
	 * this is called when the patch gets disabled and it
	 * cannot get enabled again.
	 */
	kobject_put(&patch->kobj);
	wait_for_completion(&patch->finish);

	/* Put the module after the last access to struct klp_patch. */
	if (!patch->forced)
		module_put(patch->mod);
}