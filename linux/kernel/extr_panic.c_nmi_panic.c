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
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nmi_panic_self_stop (struct pt_regs*) ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 
 int /*<<< orphan*/  panic_cpu ; 
 int raw_smp_processor_id () ; 

void nmi_panic(struct pt_regs *regs, const char *msg)
{
	int old_cpu, cpu;

	cpu = raw_smp_processor_id();
	old_cpu = atomic_cmpxchg(&panic_cpu, PANIC_CPU_INVALID, cpu);

	if (old_cpu == PANIC_CPU_INVALID)
		panic("%s", msg);
	else if (old_cpu != cpu)
		nmi_panic_self_stop(regs);
}