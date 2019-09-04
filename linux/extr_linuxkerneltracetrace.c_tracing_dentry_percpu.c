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
struct trace_array {struct dentry* percpu_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 struct dentry* tracefs_create_dir (char*,struct dentry*) ; 
 struct dentry* tracing_get_dentry (struct trace_array*) ; 

__attribute__((used)) static struct dentry *tracing_dentry_percpu(struct trace_array *tr, int cpu)
{
	struct dentry *d_tracer;

	if (tr->percpu_dir)
		return tr->percpu_dir;

	d_tracer = tracing_get_dentry(tr);
	if (IS_ERR(d_tracer))
		return NULL;

	tr->percpu_dir = tracefs_create_dir("per_cpu", d_tracer);

	WARN_ONCE(!tr->percpu_dir,
		  "Could not create tracefs directory 'per_cpu/%d'\n", cpu);

	return tr->percpu_dir;
}