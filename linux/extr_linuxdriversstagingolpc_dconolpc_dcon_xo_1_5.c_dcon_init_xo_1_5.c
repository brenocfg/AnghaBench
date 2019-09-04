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
struct dcon_priv {int /*<<< orphan*/  curr_src; int /*<<< orphan*/  pending_src; } ;
struct TYPE_2__ {unsigned int sci_interrupt; } ;

/* Variables and functions */
 int BIT_GPIO12 ; 
 int /*<<< orphan*/  DCON_SOURCE_CPU ; 
 int /*<<< orphan*/  DCON_SOURCE_DCON ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  VX855_GENL_PURPOSE_OUTPUT ; 
 int /*<<< orphan*/  VX855_GPI_SCI_SMI ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  dcon_clear_irq () ; 
 int /*<<< orphan*/  dcon_interrupt ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dcon_priv*) ; 

__attribute__((used)) static int dcon_init_xo_1_5(struct dcon_priv *dcon)
{
	unsigned int irq;

	dcon_clear_irq();

	/* set   PMIO_Rx52[6] to enable SCI/SMI on gpio12 */
	outb(inb(VX855_GPI_SCI_SMI) | BIT_GPIO12, VX855_GPI_SCI_SMI);

	/* Determine the current state of DCONLOAD, likely set by firmware */
	/* GPIO1 */
	dcon->curr_src = (inl(VX855_GENL_PURPOSE_OUTPUT) & 0x1000) ?
			DCON_SOURCE_CPU : DCON_SOURCE_DCON;
	dcon->pending_src = dcon->curr_src;

	/* we're sharing the IRQ with ACPI */
	irq = acpi_gbl_FADT.sci_interrupt;
	if (request_irq(irq, &dcon_interrupt, IRQF_SHARED, "DCON", dcon)) {
		pr_err("DCON (IRQ%d) allocation failed\n", irq);
		return 1;
	}

	return 0;
}