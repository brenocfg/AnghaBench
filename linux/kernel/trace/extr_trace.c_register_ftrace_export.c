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
struct trace_export {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  add_ftrace_export (int /*<<< orphan*/ *,struct trace_export*) ; 
 int /*<<< orphan*/  ftrace_export_lock ; 
 int /*<<< orphan*/  ftrace_exports_list ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int register_ftrace_export(struct trace_export *export)
{
	if (WARN_ON_ONCE(!export->write))
		return -1;

	mutex_lock(&ftrace_export_lock);

	add_ftrace_export(&ftrace_exports_list, export);

	mutex_unlock(&ftrace_export_lock);

	return 0;
}