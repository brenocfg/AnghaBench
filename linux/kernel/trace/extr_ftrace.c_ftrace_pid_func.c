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
struct TYPE_4__ {TYPE_1__* data; } ;
struct trace_array {TYPE_2__ trace_buffer; } ;
struct pt_regs {int dummy; } ;
struct ftrace_ops {int /*<<< orphan*/  (* saved_func ) (unsigned long,unsigned long,struct ftrace_ops*,struct pt_regs*) ;struct trace_array* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  ftrace_ignore_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long,struct ftrace_ops*,struct pt_regs*) ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftrace_pid_func(unsigned long ip, unsigned long parent_ip,
			    struct ftrace_ops *op, struct pt_regs *regs)
{
	struct trace_array *tr = op->private;

	if (tr && this_cpu_read(tr->trace_buffer.data->ftrace_ignore_pid))
		return;

	op->saved_func(ip, parent_ip, op, regs);
}