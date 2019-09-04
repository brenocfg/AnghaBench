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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  rev; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MT_ASIC_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76x2_dev*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76_mmio_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x2_dev*,int,int,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 struct mt76x2_dev* mt76x2_alloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2_irq_handler ; 
 int mt76x2_register_device (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 

__attribute__((used)) static int
mt76pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct mt76x2_dev *dev;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	if (ret)
		return ret;

	pci_set_master(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	dev = mt76x2_alloc_device(&pdev->dev);
	if (!dev)
		return -ENOMEM;

	mt76_mmio_init(&dev->mt76, pcim_iomap_table(pdev)[0]);

	dev->mt76.rev = mt76_rr(dev, MT_ASIC_VERSION);
	dev_info(dev->mt76.dev, "ASIC revision: %08x\n", dev->mt76.rev);

	ret = devm_request_irq(dev->mt76.dev, pdev->irq, mt76x2_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	if (ret)
		goto error;

	ret = mt76x2_register_device(dev);
	if (ret)
		goto error;

	/* Fix up ASPM configuration */

	/* RG_SSUSB_G1_CDR_BIR_LTR = 0x9 */
	mt76_rmw_field(dev, 0x15a10, 0x1f << 16, 0x9);

	/* RG_SSUSB_G1_CDR_BIC_LTR = 0xf */
	mt76_rmw_field(dev, 0x15a0c, 0xf << 28, 0xf);

	/* RG_SSUSB_CDR_BR_PE1D = 0x3 */
	mt76_rmw_field(dev, 0x15c58, 0x3 << 6, 0x3);

	return 0;

error:
	ieee80211_free_hw(mt76_hw(dev));
	return ret;
}