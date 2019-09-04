#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct switchtec_dev {TYPE_2__* pdev; TYPE_1__* mmio_part_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vep_vector_number; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct switchtec_dev*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int pci_alloc_irq_vectors (TYPE_2__*,int,int,int) ; 
 int pci_irq_vector (TYPE_2__*,int) ; 
 int /*<<< orphan*/  switchtec_event_isr ; 

__attribute__((used)) static int switchtec_init_isr(struct switchtec_dev *stdev)
{
	int nvecs;
	int event_irq;

	nvecs = pci_alloc_irq_vectors(stdev->pdev, 1, 4,
				      PCI_IRQ_MSIX | PCI_IRQ_MSI);
	if (nvecs < 0)
		return nvecs;

	event_irq = ioread32(&stdev->mmio_part_cfg->vep_vector_number);
	if (event_irq < 0 || event_irq >= nvecs)
		return -EFAULT;

	event_irq = pci_irq_vector(stdev->pdev, event_irq);
	if (event_irq < 0)
		return event_irq;

	return devm_request_irq(&stdev->pdev->dev, event_irq,
				switchtec_event_isr, 0,
				KBUILD_MODNAME, stdev);
}