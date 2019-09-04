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
struct xen_pcibk_dev_data {int enable_intx; int ack_intr; int isr_on; scalar_t__ irq; int /*<<< orphan*/  irq_name; } ;
struct pci_dev {scalar_t__ hdr_type; scalar_t__ irq; scalar_t__ msix_enabled; scalar_t__ msi_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pci_dev*) ; 
 struct xen_pcibk_dev_data* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_is_enabled (struct pci_dev*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  xen_pcibk_guest_interrupt ; 

__attribute__((used)) static void xen_pcibk_control_isr(struct pci_dev *dev, int reset)
{
	struct xen_pcibk_dev_data *dev_data;
	int rc;
	int enable = 0;

	dev_data = pci_get_drvdata(dev);
	if (!dev_data)
		return;

	/* We don't deal with bridges */
	if (dev->hdr_type != PCI_HEADER_TYPE_NORMAL)
		return;

	if (reset) {
		dev_data->enable_intx = 0;
		dev_data->ack_intr = 0;
	}
	enable =  dev_data->enable_intx;

	/* Asked to disable, but ISR isn't runnig */
	if (!enable && !dev_data->isr_on)
		return;

	/* Squirrel away the IRQs in the dev_data. We need this
	 * b/c when device transitions to MSI, the dev->irq is
	 * overwritten with the MSI vector.
	 */
	if (enable)
		dev_data->irq = dev->irq;

	/*
	 * SR-IOV devices in all use MSI-X and have no legacy
	 * interrupts, so inhibit creating a fake IRQ handler for them.
	 */
	if (dev_data->irq == 0)
		goto out;

	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s-> %s\n",
		dev_data->irq_name,
		dev_data->irq,
		pci_is_enabled(dev) ? "on" : "off",
		dev->msi_enabled ? "MSI" : "",
		dev->msix_enabled ? "MSI/X" : "",
		dev_data->isr_on ? "enable" : "disable",
		enable ? "enable" : "disable");

	if (enable) {
		/*
		 * The MSI or MSI-X should not have an IRQ handler. Otherwise
		 * if the guest terminates we BUG_ON in free_msi_irqs.
		 */
		if (dev->msi_enabled || dev->msix_enabled)
			goto out;

		rc = request_irq(dev_data->irq,
				xen_pcibk_guest_interrupt, IRQF_SHARED,
				dev_data->irq_name, dev);
		if (rc) {
			dev_err(&dev->dev, "%s: failed to install fake IRQ " \
				"handler for IRQ %d! (rc:%d)\n",
				dev_data->irq_name, dev_data->irq, rc);
			goto out;
		}
	} else {
		free_irq(dev_data->irq, dev);
		dev_data->irq = 0;
	}
	dev_data->isr_on = enable;
	dev_data->ack_intr = enable;
out:
	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s\n",
		dev_data->irq_name,
		dev_data->irq,
		pci_is_enabled(dev) ? "on" : "off",
		dev->msi_enabled ? "MSI" : "",
		dev->msix_enabled ? "MSI/X" : "",
		enable ? (dev_data->isr_on ? "enabled" : "failed to enable") :
			(dev_data->isr_on ? "failed to disable" : "disabled"));
}