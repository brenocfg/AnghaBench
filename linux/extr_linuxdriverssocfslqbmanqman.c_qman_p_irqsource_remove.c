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
typedef  int /*<<< orphan*/  u32 ;
struct qman_portal {int /*<<< orphan*/  p; int /*<<< orphan*/  irq_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_PIRQ_VISIBLE ; 
 int /*<<< orphan*/  QM_REG_IER ; 
 int /*<<< orphan*/  QM_REG_ISR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  qm_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qman_p_irqsource_remove(struct qman_portal *p, u32 bits)
{
	unsigned long irqflags;
	u32 ier;

	/*
	 * Our interrupt handler only processes+clears status register bits that
	 * are in p->irq_sources. As we're trimming that mask, if one of them
	 * were to assert in the status register just before we remove it from
	 * the enable register, there would be an interrupt-storm when we
	 * release the IRQ lock. So we wait for the enable register update to
	 * take effect in h/w (by reading it back) and then clear all other bits
	 * in the status register. Ie. we clear them from ISR once it's certain
	 * IER won't allow them to reassert.
	 */
	local_irq_save(irqflags);
	bits &= QM_PIRQ_VISIBLE;
	p->irq_sources &= ~bits;
	qm_out(&p->p, QM_REG_IER, p->irq_sources);
	ier = qm_in(&p->p, QM_REG_IER);
	/*
	 * Using "~ier" (rather than "bits" or "~p->irq_sources") creates a
	 * data-dependency, ie. to protect against re-ordering.
	 */
	qm_out(&p->p, QM_REG_ISR, ~ier);
	local_irq_restore(irqflags);
}