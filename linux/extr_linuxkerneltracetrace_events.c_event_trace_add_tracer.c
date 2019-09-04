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
struct trace_array {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_add_event_dirs (struct trace_array*) ; 
 int create_event_toplevel_files (struct dentry*,struct trace_array*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_event_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int event_trace_add_tracer(struct dentry *parent, struct trace_array *tr)
{
	int ret;

	lockdep_assert_held(&event_mutex);

	ret = create_event_toplevel_files(parent, tr);
	if (ret)
		goto out;

	down_write(&trace_event_sem);
	__trace_add_event_dirs(tr);
	up_write(&trace_event_sem);

 out:
	return ret;
}