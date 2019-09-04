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
struct irqaction {int flags; } ;
struct irq_desc {struct irqaction* action; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 int IRQF_IRQPOLL ; 
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  barrier () ; 
 int irqfixup ; 

__attribute__((used)) static inline int
try_misrouted_irq(unsigned int irq, struct irq_desc *desc,
		  irqreturn_t action_ret)
{
	struct irqaction *action;

	if (!irqfixup)
		return 0;

	/* We didn't actually handle the IRQ - see if it was misrouted? */
	if (action_ret == IRQ_NONE)
		return 1;

	/*
	 * But for 'irqfixup == 2' we also do it for handled interrupts if
	 * they are marked as IRQF_IRQPOLL (or for irq zero, which is the
	 * traditional PC timer interrupt.. Legacy)
	 */
	if (irqfixup < 2)
		return 0;

	if (!irq)
		return 1;

	/*
	 * Since we don't get the descriptor lock, "action" can
	 * change under us.  We don't really care, but we don't
	 * want to follow a NULL pointer. So tell the compiler to
	 * just load it once by using a barrier.
	 */
	action = desc->action;
	barrier();
	return action && (action->flags & IRQF_IRQPOLL);
}