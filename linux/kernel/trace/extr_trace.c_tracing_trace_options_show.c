#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tracer_opt {int bit; scalar_t__ name; } ;
struct trace_array {int trace_flags; TYPE_2__* current_trace; } ;
struct seq_file {struct trace_array* private; } ;
struct TYPE_4__ {TYPE_1__* flags; } ;
struct TYPE_3__ {int val; struct tracer_opt* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 scalar_t__* trace_options ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static int tracing_trace_options_show(struct seq_file *m, void *v)
{
	struct tracer_opt *trace_opts;
	struct trace_array *tr = m->private;
	u32 tracer_flags;
	int i;

	mutex_lock(&trace_types_lock);
	tracer_flags = tr->current_trace->flags->val;
	trace_opts = tr->current_trace->flags->opts;

	for (i = 0; trace_options[i]; i++) {
		if (tr->trace_flags & (1 << i))
			seq_printf(m, "%s\n", trace_options[i]);
		else
			seq_printf(m, "no%s\n", trace_options[i]);
	}

	for (i = 0; trace_opts[i].name; i++) {
		if (tracer_flags & trace_opts[i].bit)
			seq_printf(m, "%s\n", trace_opts[i].name);
		else
			seq_printf(m, "no%s\n", trace_opts[i].name);
	}
	mutex_unlock(&trace_types_lock);

	return 0;
}