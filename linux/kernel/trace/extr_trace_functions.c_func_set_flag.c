#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct trace_array {TYPE_1__* ops; int /*<<< orphan*/ * current_trace; } ;
struct TYPE_5__ {int const val; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TRACE_FUNC_OPT_STACK 128 
 TYPE_3__ func_flags ; 
 int /*<<< orphan*/  function_stack_trace_call ; 
 int /*<<< orphan*/  function_trace ; 
 int /*<<< orphan*/  function_trace_call ; 
 int /*<<< orphan*/  register_ftrace_function (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_ftrace_function (TYPE_1__*) ; 

__attribute__((used)) static int
func_set_flag(struct trace_array *tr, u32 old_flags, u32 bit, int set)
{
	switch (bit) {
	case TRACE_FUNC_OPT_STACK:
		/* do nothing if already set */
		if (!!set == !!(func_flags.val & TRACE_FUNC_OPT_STACK))
			break;

		/* We can change this flag when not running. */
		if (tr->current_trace != &function_trace)
			break;

		unregister_ftrace_function(tr->ops);

		if (set) {
			tr->ops->func = function_stack_trace_call;
			register_ftrace_function(tr->ops);
		} else {
			tr->ops->func = function_trace_call;
			register_ftrace_function(tr->ops);
		}

		break;
	default:
		return -EINVAL;
	}

	return 0;
}