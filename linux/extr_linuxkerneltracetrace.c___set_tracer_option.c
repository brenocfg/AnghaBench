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
struct tracer_opt {int /*<<< orphan*/  bit; } ;
struct tracer_flags {int /*<<< orphan*/  val; struct tracer* trace; } ;
struct tracer {int (* set_flag ) (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int stub1 (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __set_tracer_option(struct trace_array *tr,
			       struct tracer_flags *tracer_flags,
			       struct tracer_opt *opts, int neg)
{
	struct tracer *trace = tracer_flags->trace;
	int ret;

	ret = trace->set_flag(tr, tracer_flags->val, opts->bit, !neg);
	if (ret)
		return ret;

	if (neg)
		tracer_flags->val &= ~opts->bit;
	else
		tracer_flags->val |= opts->bit;
	return 0;
}