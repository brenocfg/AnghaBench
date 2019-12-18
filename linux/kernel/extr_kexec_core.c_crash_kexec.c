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

/* Variables and functions */
 int PANIC_CPU_INVALID ; 
 int /*<<< orphan*/  __crash_kexec (struct pt_regs*) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic_cpu ; 
 int /*<<< orphan*/  printk_safe_flush_on_panic () ; 
 int raw_smp_processor_id () ; 

void crash_kexec(struct pt_regs *regs)
{
	int old_cpu, this_cpu;

	/*
	 * Only one CPU is allowed to execute the crash_kexec() code as with
	 * panic().  Otherwise parallel calls of panic() and crash_kexec()
	 * may stop each other.  To exclude them, we use panic_cpu here too.
	 */
	this_cpu = raw_smp_processor_id();
	old_cpu = atomic_cmpxchg(&panic_cpu, PANIC_CPU_INVALID, this_cpu);
	if (old_cpu == PANIC_CPU_INVALID) {
		/* This is the 1st CPU which comes here, so go ahead. */
		printk_safe_flush_on_panic();
		__crash_kexec(regs);

		/*
		 * Reset panic_cpu to allow another panic()/crash_kexec()
		 * call.
		 */
		atomic_set(&panic_cpu, PANIC_CPU_INVALID);
	}
}