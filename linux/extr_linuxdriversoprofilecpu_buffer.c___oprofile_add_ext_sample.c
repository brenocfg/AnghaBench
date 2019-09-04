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
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;
struct oprofile_cpu_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* backtrace ) (struct pt_regs* const,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  log_sample (struct oprofile_cpu_buffer*,unsigned long,unsigned long,int,unsigned long,struct task_struct*) ; 
 int /*<<< orphan*/  op_cpu_buffer ; 
 unsigned long oprofile_backtrace_depth ; 
 int /*<<< orphan*/  oprofile_begin_trace (struct oprofile_cpu_buffer*) ; 
 int /*<<< orphan*/  oprofile_end_trace (struct oprofile_cpu_buffer*) ; 
 TYPE_1__ oprofile_ops ; 
 int /*<<< orphan*/  stub1 (struct pt_regs* const,unsigned long) ; 
 struct oprofile_cpu_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__oprofile_add_ext_sample(unsigned long pc, struct pt_regs * const regs,
			  unsigned long event, int is_kernel,
			  struct task_struct *task)
{
	struct oprofile_cpu_buffer *cpu_buf = this_cpu_ptr(&op_cpu_buffer);
	unsigned long backtrace = oprofile_backtrace_depth;

	/*
	 * if log_sample() fail we can't backtrace since we lost the
	 * source of this event
	 */
	if (!log_sample(cpu_buf, pc, backtrace, is_kernel, event, task))
		/* failed */
		return;

	if (!backtrace)
		return;

	oprofile_begin_trace(cpu_buf);
	oprofile_ops.backtrace(regs, backtrace);
	oprofile_end_trace(cpu_buf);
}