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
struct irq_poll {int /*<<< orphan*/  state; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_POLL_F_SCHED ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void __irq_poll_complete(struct irq_poll *iop)
{
	list_del(&iop->list);
	smp_mb__before_atomic();
	clear_bit_unlock(IRQ_POLL_F_SCHED, &iop->state);
}