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
struct ftrace_ops {int dummy; } ;

/* Variables and functions */
 scalar_t__ MCOUNT_INSN_SIZE ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  disable_stack_tracer ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  rcu_is_watching () ; 

__attribute__((used)) static void
stack_trace_call(unsigned long ip, unsigned long parent_ip,
		 struct ftrace_ops *op, struct pt_regs *pt_regs)
{
	unsigned long stack;

	preempt_disable_notrace();

	/* no atomic needed, we only modify this variable by this cpu */
	__this_cpu_inc(disable_stack_tracer);
	if (__this_cpu_read(disable_stack_tracer) != 1)
		goto out;

	/* If rcu is not watching, then save stack trace can fail */
	if (!rcu_is_watching())
		goto out;

	ip += MCOUNT_INSN_SIZE;

	check_stack(ip, &stack);

 out:
	__this_cpu_dec(disable_stack_tracer);
	/* prevent recursion in schedule */
	preempt_enable_notrace();
}