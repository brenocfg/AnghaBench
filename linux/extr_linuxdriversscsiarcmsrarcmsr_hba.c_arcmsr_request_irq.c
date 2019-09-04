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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct AdapterControlBlock {int vector_count; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ARCMST_NUM_MSIX_VECTORS ; 
 int FAILED ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_IRQ_LEGACY ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int SUCCESS ; 
 int /*<<< orphan*/  arcmsr_do_interrupt ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct AdapterControlBlock*) ; 
 int msi_enable ; 
 scalar_t__ msix_enable ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char*,struct AdapterControlBlock*) ; 

__attribute__((used)) static int
arcmsr_request_irq(struct pci_dev *pdev, struct AdapterControlBlock *acb)
{
	unsigned long flags;
	int nvec, i;

	if (msix_enable == 0)
		goto msi_int0;
	nvec = pci_alloc_irq_vectors(pdev, 1, ARCMST_NUM_MSIX_VECTORS,
			PCI_IRQ_MSIX);
	if (nvec > 0) {
		pr_info("arcmsr%d: msi-x enabled\n", acb->host->host_no);
		flags = 0;
	} else {
msi_int0:
		if (msi_enable == 1) {
			nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
			if (nvec == 1) {
				dev_info(&pdev->dev, "msi enabled\n");
				goto msi_int1;
			}
		}
		nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_LEGACY);
		if (nvec < 1)
			return FAILED;
msi_int1:
		flags = IRQF_SHARED;
	}

	acb->vector_count = nvec;
	for (i = 0; i < nvec; i++) {
		if (request_irq(pci_irq_vector(pdev, i), arcmsr_do_interrupt,
				flags, "arcmsr", acb)) {
			pr_warn("arcmsr%d: request_irq =%d failed!\n",
				acb->host->host_no, pci_irq_vector(pdev, i));
			goto out_free_irq;
		}
	}

	return SUCCESS;
out_free_irq:
	while (--i >= 0)
		free_irq(pci_irq_vector(pdev, i), acb);
	pci_free_irq_vectors(pdev);
	return FAILED;
}