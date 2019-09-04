#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tpi_info {int /*<<< orphan*/  schid; scalar_t__ intparm; } ;
struct TYPE_4__ {int /*<<< orphan*/  scsw; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_2__* driver; TYPE_1__ schib; } ;
struct irb {int /*<<< orphan*/  scsw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  int_code; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq ) (struct subchannel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_NOHZ_DELAY ; 
 int /*<<< orphan*/  IRQIO_CIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cio_irb ; 
 TYPE_3__* get_irq_regs () ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_cpu_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct subchannel*) ; 
 struct irb* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_s390_cio_interrupt (struct tpi_info*) ; 
 scalar_t__ tsch (int /*<<< orphan*/ ,struct irb*) ; 

__attribute__((used)) static irqreturn_t do_cio_interrupt(int irq, void *dummy)
{
	struct tpi_info *tpi_info;
	struct subchannel *sch;
	struct irb *irb;

	set_cpu_flag(CIF_NOHZ_DELAY);
	tpi_info = (struct tpi_info *) &get_irq_regs()->int_code;
	trace_s390_cio_interrupt(tpi_info);
	irb = this_cpu_ptr(&cio_irb);
	sch = (struct subchannel *)(unsigned long) tpi_info->intparm;
	if (!sch) {
		/* Clear pending interrupt condition. */
		inc_irq_stat(IRQIO_CIO);
		tsch(tpi_info->schid, irb);
		return IRQ_HANDLED;
	}
	spin_lock(sch->lock);
	/* Store interrupt response block to lowcore. */
	if (tsch(tpi_info->schid, irb) == 0) {
		/* Keep subchannel information word up to date. */
		memcpy (&sch->schib.scsw, &irb->scsw, sizeof (irb->scsw));
		/* Call interrupt handler if there is one. */
		if (sch->driver && sch->driver->irq)
			sch->driver->irq(sch);
		else
			inc_irq_stat(IRQIO_CIO);
	} else
		inc_irq_stat(IRQIO_CIO);
	spin_unlock(sch->lock);

	return IRQ_HANDLED;
}