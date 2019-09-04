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
struct mips_ejtag_fdc_tty {scalar_t__ cpu; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CAUSEF_FDCI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  mips_ejtag_fdc_handle (struct mips_ejtag_fdc_tty*) ; 
 int read_c0_cause () ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static irqreturn_t mips_ejtag_fdc_isr(int irq, void *dev_id)
{
	struct mips_ejtag_fdc_tty *priv = dev_id;

	/*
	 * We're not using proper per-cpu IRQs, so we must be careful not to
	 * handle IRQs on CPUs we're not interested in.
	 *
	 * Ideally proper per-cpu IRQ handlers could be used, but that doesn't
	 * fit well with the whole sharing of the main CPU IRQ lines. When we
	 * have something with a GIC that routes the FDC IRQs (i.e. no sharing
	 * between handlers) then support could be added more easily.
	 */
	if (smp_processor_id() != priv->cpu)
		return IRQ_NONE;

	/* If no FDC interrupt pending, it wasn't for us */
	if (!(read_c0_cause() & CAUSEF_FDCI))
		return IRQ_NONE;

	mips_ejtag_fdc_handle(priv);
	return IRQ_HANDLED;
}