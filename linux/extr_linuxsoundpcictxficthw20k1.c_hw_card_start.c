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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct hw {scalar_t__ model; void* io_base; int /*<<< orphan*/  irq; TYPE_1__* card; struct pci_dev* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 scalar_t__ CTUAA ; 
 int /*<<< orphan*/  DMA_BIT_MASK (unsigned int const) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  ct_20k1_interrupt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hw*) ; 
 int uaa_to_xfi (struct pci_dev*) ; 

__attribute__((used)) static int hw_card_start(struct hw *hw)
{
	int err;
	struct pci_dev *pci = hw->pci;
	const unsigned int dma_bits = BITS_PER_LONG;

	err = pci_enable_device(pci);
	if (err < 0)
		return err;

	/* Set DMA transfer mask */
	if (!dma_set_mask(&pci->dev, DMA_BIT_MASK(dma_bits))) {
		dma_set_coherent_mask(&pci->dev, DMA_BIT_MASK(dma_bits));
	} else {
		dma_set_mask(&pci->dev, DMA_BIT_MASK(32));
		dma_set_coherent_mask(&pci->dev, DMA_BIT_MASK(32));
	}

	if (!hw->io_base) {
		err = pci_request_regions(pci, "XFi");
		if (err < 0)
			goto error1;

		if (hw->model == CTUAA)
			hw->io_base = pci_resource_start(pci, 5);
		else
			hw->io_base = pci_resource_start(pci, 0);

	}

	/* Switch to X-Fi mode from UAA mode if neeeded */
	if (hw->model == CTUAA) {
		err = uaa_to_xfi(pci);
		if (err)
			goto error2;

	}

	if (hw->irq < 0) {
		err = request_irq(pci->irq, ct_20k1_interrupt, IRQF_SHARED,
				  KBUILD_MODNAME, hw);
		if (err < 0) {
			dev_err(hw->card->dev,
				"XFi: Cannot get irq %d\n", pci->irq);
			goto error2;
		}
		hw->irq = pci->irq;
	}

	pci_set_master(pci);

	return 0;

error2:
	pci_release_regions(pci);
	hw->io_base = 0;
error1:
	pci_disable_device(pci);
	return err;
}