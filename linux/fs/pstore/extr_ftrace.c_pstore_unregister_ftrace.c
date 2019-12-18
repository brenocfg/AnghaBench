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

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstore_ftrace_dir ; 
 int pstore_ftrace_enabled ; 
 int /*<<< orphan*/  pstore_ftrace_lock ; 
 int /*<<< orphan*/  pstore_ftrace_ops ; 
 int /*<<< orphan*/  unregister_ftrace_function (int /*<<< orphan*/ *) ; 

void pstore_unregister_ftrace(void)
{
	mutex_lock(&pstore_ftrace_lock);
	if (pstore_ftrace_enabled) {
		unregister_ftrace_function(&pstore_ftrace_ops);
		pstore_ftrace_enabled = false;
	}
	mutex_unlock(&pstore_ftrace_lock);

	debugfs_remove_recursive(pstore_ftrace_dir);
}