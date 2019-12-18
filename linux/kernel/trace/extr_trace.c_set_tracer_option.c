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
struct tracer_opt {scalar_t__ name; } ;
struct tracer_flags {struct tracer_opt* opts; } ;
struct tracer {struct tracer_flags* flags; } ;
struct trace_array {struct tracer* current_trace; } ;

/* Variables and functions */
 int EINVAL ; 
 int __set_tracer_option (struct trace_array*,struct tracer_flags*,struct tracer_opt*,int) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 

__attribute__((used)) static int set_tracer_option(struct trace_array *tr, char *cmp, int neg)
{
	struct tracer *trace = tr->current_trace;
	struct tracer_flags *tracer_flags = trace->flags;
	struct tracer_opt *opts = NULL;
	int i;

	for (i = 0; tracer_flags->opts[i].name; i++) {
		opts = &tracer_flags->opts[i];

		if (strcmp(cmp, opts->name) == 0)
			return __set_tracer_option(tr, trace->flags, opts, neg);
	}

	return -EINVAL;
}