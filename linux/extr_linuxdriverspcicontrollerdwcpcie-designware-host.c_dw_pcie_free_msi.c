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
struct pcie_port {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  msi_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dw_pcie_free_msi(struct pcie_port *pp)
{
	irq_set_chained_handler(pp->msi_irq, NULL);
	irq_set_handler_data(pp->msi_irq, NULL);

	irq_domain_remove(pp->msi_domain);
	irq_domain_remove(pp->irq_domain);
}