#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct warn_args {int /*<<< orphan*/  args; int /*<<< orphan*/  fmt; } ;
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_STILL_OK ; 
 int /*<<< orphan*/  add_taint (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  disable_trace_on_warning () ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_warn ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,...) ; 
 int /*<<< orphan*/  print_irqtrace_events (TYPE_1__*) ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  print_oops_end_marker () ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  vprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __warn(const char *file, int line, void *caller, unsigned taint,
	    struct pt_regs *regs, struct warn_args *args)
{
	disable_trace_on_warning();

	if (file)
		pr_warn("WARNING: CPU: %d PID: %d at %s:%d %pS\n",
			raw_smp_processor_id(), current->pid, file, line,
			caller);
	else
		pr_warn("WARNING: CPU: %d PID: %d at %pS\n",
			raw_smp_processor_id(), current->pid, caller);

	if (args)
		vprintk(args->fmt, args->args);

	if (panic_on_warn) {
		/*
		 * This thread may hit another WARN() in the panic path.
		 * Resetting this prevents additional WARN() from panicking the
		 * system on this thread.  Other threads are blocked by the
		 * panic_mutex in panic().
		 */
		panic_on_warn = 0;
		panic("panic_on_warn set ...\n");
	}

	print_modules();

	if (regs)
		show_regs(regs);
	else
		dump_stack();

	print_irqtrace_events(current);

	print_oops_end_marker();

	/* Just a warning, don't kill lockdep. */
	add_taint(taint, LOCKDEP_STILL_OK);
}