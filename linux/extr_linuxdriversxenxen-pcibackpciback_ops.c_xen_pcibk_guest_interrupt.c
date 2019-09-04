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
struct xen_pcibk_dev_data {int handled; scalar_t__ ack_intr; int /*<<< orphan*/  irq_name; scalar_t__ isr_on; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct xen_pcibk_dev_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xen_test_irq_shared (int) ; 

__attribute__((used)) static irqreturn_t xen_pcibk_guest_interrupt(int irq, void *dev_id)
{
	struct pci_dev *dev = (struct pci_dev *)dev_id;
	struct xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	if (dev_data->isr_on && dev_data->ack_intr) {
		dev_data->handled++;
		if ((dev_data->handled % 1000) == 0) {
			if (xen_test_irq_shared(irq)) {
				pr_info("%s IRQ line is not shared "
					"with other domains. Turning ISR off\n",
					 dev_data->irq_name);
				dev_data->ack_intr = 0;
			}
		}
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}