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
struct pt_regs {int dummy; } ;
struct ftrace_ops {int flags; int /*<<< orphan*/  (* func ) (unsigned long,unsigned long,struct ftrace_ops*,struct pt_regs*) ;} ;

/* Variables and functions */
 int FTRACE_OPS_FL_RCU ; 
 int /*<<< orphan*/  TRACE_LIST_MAX ; 
 int /*<<< orphan*/  TRACE_LIST_START ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long,struct ftrace_ops*,struct pt_regs*) ; 
 int /*<<< orphan*/  trace_clear_recursion (int) ; 
 int trace_test_and_set_recursion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftrace_ops_assist_func(unsigned long ip, unsigned long parent_ip,
				   struct ftrace_ops *op, struct pt_regs *regs)
{
	int bit;

	if ((op->flags & FTRACE_OPS_FL_RCU) && !rcu_is_watching())
		return;

	bit = trace_test_and_set_recursion(TRACE_LIST_START, TRACE_LIST_MAX);
	if (bit < 0)
		return;

	preempt_disable_notrace();

	op->func(ip, parent_ip, op, regs);

	preempt_enable_notrace();
	trace_clear_recursion(bit);
}