#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_probe {int nr_args; struct probe_arg* args; } ;
struct trace_event_call {int dummy; } ;
struct probe_arg {char* fmt; int count; TYPE_1__* type; scalar_t__ offset; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* fmttype; int size; int /*<<< orphan*/  is_signed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_OTHER ; 
 int trace_define_field (struct trace_event_call*,char const*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int traceprobe_define_arg_fields(struct trace_event_call *event_call,
				 size_t offset, struct trace_probe *tp)
{
	int ret, i;

	/* Set argument names as fields */
	for (i = 0; i < tp->nr_args; i++) {
		struct probe_arg *parg = &tp->args[i];
		const char *fmt = parg->type->fmttype;
		int size = parg->type->size;

		if (parg->fmt)
			fmt = parg->fmt;
		if (parg->count)
			size *= parg->count;
		ret = trace_define_field(event_call, fmt, parg->name,
					 offset + parg->offset, size,
					 parg->type->is_signed,
					 FILTER_OTHER);
		if (ret)
			return ret;
	}
	return 0;
}