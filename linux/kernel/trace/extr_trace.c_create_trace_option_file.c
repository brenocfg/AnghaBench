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
struct tracer_opt {int /*<<< orphan*/  name; } ;
struct tracer_flags {int dummy; } ;
struct trace_option_dentry {int /*<<< orphan*/  entry; struct trace_array* tr; struct tracer_opt* opt; struct tracer_flags* flags; } ;
struct trace_array {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct trace_option_dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_options_fops ; 
 struct dentry* trace_options_init_dentry (struct trace_array*) ; 

__attribute__((used)) static void
create_trace_option_file(struct trace_array *tr,
			 struct trace_option_dentry *topt,
			 struct tracer_flags *flags,
			 struct tracer_opt *opt)
{
	struct dentry *t_options;

	t_options = trace_options_init_dentry(tr);
	if (!t_options)
		return;

	topt->flags = flags;
	topt->opt = opt;
	topt->tr = tr;

	topt->entry = trace_create_file(opt->name, 0644, t_options, topt,
				    &trace_options_fops);

}