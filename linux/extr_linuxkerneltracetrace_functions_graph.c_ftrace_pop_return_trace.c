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
struct ftrace_graph_ret {scalar_t__ depth; int /*<<< orphan*/  overrun; int /*<<< orphan*/  calltime; int /*<<< orphan*/  func; } ;
struct TYPE_4__ {int curr_ret_stack; int /*<<< orphan*/  curr_ret_depth; int /*<<< orphan*/  trace_overrun; TYPE_1__* ret_stack; } ;
struct TYPE_3__ {unsigned long ret; int /*<<< orphan*/  calltime; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 scalar_t__ FTRACE_NOTRACE_DEPTH ; 
 int FTRACE_RETFUNC_DEPTH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ftrace_graph_stop () ; 
 scalar_t__ panic ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ftrace_pop_return_trace(struct ftrace_graph_ret *trace, unsigned long *ret,
			unsigned long frame_pointer)
{
	int index;

	index = current->curr_ret_stack;

	/*
	 * A negative index here means that it's just returned from a
	 * notrace'd function.  Recover index to get an original
	 * return address.  See ftrace_push_return_trace().
	 *
	 * TODO: Need to check whether the stack gets corrupted.
	 */
	if (index < 0)
		index += FTRACE_NOTRACE_DEPTH;

	if (unlikely(index < 0 || index >= FTRACE_RETFUNC_DEPTH)) {
		ftrace_graph_stop();
		WARN_ON(1);
		/* Might as well panic, otherwise we have no where to go */
		*ret = (unsigned long)panic;
		return;
	}

#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	/*
	 * The arch may choose to record the frame pointer used
	 * and check it here to make sure that it is what we expect it
	 * to be. If gcc does not set the place holder of the return
	 * address in the frame pointer, and does a copy instead, then
	 * the function graph trace will fail. This test detects this
	 * case.
	 *
	 * Currently, x86_32 with optimize for size (-Os) makes the latest
	 * gcc do the above.
	 *
	 * Note, -mfentry does not use frame pointers, and this test
	 *  is not needed if CC_USING_FENTRY is set.
	 */
	if (unlikely(current->ret_stack[index].fp != frame_pointer)) {
		ftrace_graph_stop();
		WARN(1, "Bad frame pointer: expected %lx, received %lx\n"
		     "  from func %ps return to %lx\n",
		     current->ret_stack[index].fp,
		     frame_pointer,
		     (void *)current->ret_stack[index].func,
		     current->ret_stack[index].ret);
		*ret = (unsigned long)panic;
		return;
	}
#endif

	*ret = current->ret_stack[index].ret;
	trace->func = current->ret_stack[index].func;
	trace->calltime = current->ret_stack[index].calltime;
	trace->overrun = atomic_read(&current->trace_overrun);
	trace->depth = current->curr_ret_depth--;
	/*
	 * We still want to trace interrupts coming in if
	 * max_depth is set to 1. Make sure the decrement is
	 * seen before ftrace_graph_return.
	 */
	barrier();
}