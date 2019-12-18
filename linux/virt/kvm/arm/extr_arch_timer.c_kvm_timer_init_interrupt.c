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

/* Variables and functions */
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_ptimer_irq ; 
 int /*<<< orphan*/  host_ptimer_irq_flags ; 
 int /*<<< orphan*/  host_vtimer_irq ; 
 int /*<<< orphan*/  host_vtimer_irq_flags ; 

__attribute__((used)) static void kvm_timer_init_interrupt(void *info)
{
	enable_percpu_irq(host_vtimer_irq, host_vtimer_irq_flags);
	enable_percpu_irq(host_ptimer_irq, host_ptimer_irq_flags);
}