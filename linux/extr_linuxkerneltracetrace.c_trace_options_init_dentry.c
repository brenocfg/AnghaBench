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
struct trace_array {struct dentry* options; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct dentry* tracefs_create_dir (char*,struct dentry*) ; 
 struct dentry* tracing_get_dentry (struct trace_array*) ; 

__attribute__((used)) static struct dentry *trace_options_init_dentry(struct trace_array *tr)
{
	struct dentry *d_tracer;

	if (tr->options)
		return tr->options;

	d_tracer = tracing_get_dentry(tr);
	if (IS_ERR(d_tracer))
		return NULL;

	tr->options = tracefs_create_dir("options", d_tracer);
	if (!tr->options) {
		pr_warn("Could not create tracefs directory 'options'\n");
		return NULL;
	}

	return tr->options;
}