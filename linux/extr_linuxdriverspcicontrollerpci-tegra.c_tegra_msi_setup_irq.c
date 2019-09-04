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
struct tegra_msi {int /*<<< orphan*/  phys; int /*<<< orphan*/  domain; } ;
struct pci_dev {int dummy; } ;
struct msi_msg {int data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct msi_desc {int dummy; } ;
struct msi_controller {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_msi_desc (unsigned int,struct msi_desc*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_msi_msg (unsigned int,struct msi_msg*) ; 
 int tegra_msi_alloc (struct tegra_msi*) ; 
 int /*<<< orphan*/  tegra_msi_free (struct tegra_msi*,int) ; 
 struct tegra_msi* to_tegra_msi (struct msi_controller*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_msi_setup_irq(struct msi_controller *chip,
			       struct pci_dev *pdev, struct msi_desc *desc)
{
	struct tegra_msi *msi = to_tegra_msi(chip);
	struct msi_msg msg;
	unsigned int irq;
	int hwirq;

	hwirq = tegra_msi_alloc(msi);
	if (hwirq < 0)
		return hwirq;

	irq = irq_create_mapping(msi->domain, hwirq);
	if (!irq) {
		tegra_msi_free(msi, hwirq);
		return -EINVAL;
	}

	irq_set_msi_desc(irq, desc);

	msg.address_lo = lower_32_bits(msi->phys);
	msg.address_hi = upper_32_bits(msi->phys);
	msg.data = hwirq;

	pci_write_msi_msg(irq, &msg);

	return 0;
}