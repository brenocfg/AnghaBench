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
typedef  int u32 ;
struct qe_ic {int /*<<< orphan*/  regs; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  mask_reg; } ;

/* Variables and functions */
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 struct qe_ic* qe_ic_from_irq_data (struct irq_data*) ; 
 TYPE_1__* qe_ic_info ; 
 int /*<<< orphan*/  qe_ic_lock ; 
 int qe_ic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qe_ic_unmask_irq(struct irq_data *d)
{
	struct qe_ic *qe_ic = qe_ic_from_irq_data(d);
	unsigned int src = irqd_to_hwirq(d);
	unsigned long flags;
	u32 temp;

	raw_spin_lock_irqsave(&qe_ic_lock, flags);

	temp = qe_ic_read(qe_ic->regs, qe_ic_info[src].mask_reg);
	qe_ic_write(qe_ic->regs, qe_ic_info[src].mask_reg,
		    temp | qe_ic_info[src].mask);

	raw_spin_unlock_irqrestore(&qe_ic_lock, flags);
}