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
struct tegra_msi {int dummy; } ;
struct msi_controller {int dummy; } ;
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  tegra_msi_free (struct tegra_msi*,int /*<<< orphan*/ ) ; 
 struct tegra_msi* to_tegra_msi (struct msi_controller*) ; 

__attribute__((used)) static void tegra_msi_teardown_irq(struct msi_controller *chip,
				   unsigned int irq)
{
	struct tegra_msi *msi = to_tegra_msi(chip);
	struct irq_data *d = irq_get_irq_data(irq);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	irq_dispose_mapping(irq);
	tegra_msi_free(msi, hwirq);
}