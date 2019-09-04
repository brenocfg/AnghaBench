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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct pch_dev {scalar_t__ mem_base; int /*<<< orphan*/  mem_size; TYPE_2__* regs; int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  register_lock; struct pci_dev* pdev; int /*<<< orphan*/  irq; int /*<<< orphan*/  caps; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int /*<<< orphan*/  event; int /*<<< orphan*/  trgt_hi; int /*<<< orphan*/  trgt_lo; int /*<<< orphan*/  addend; } ;
struct TYPE_4__ {int /*<<< orphan*/  station; } ;

/* Variables and functions */
 int DEFAULT_ADDEND ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IO_MEM_BAR ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PCH_TSE_TTIPEND ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (TYPE_2__*) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isr ; 
 int /*<<< orphan*/  kfree (struct pch_dev*) ; 
 struct pch_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_eth_enable_set (struct pch_dev*) ; 
 TYPE_1__ pch_param ; 
 int /*<<< orphan*/  pch_reset (struct pch_dev*) ; 
 scalar_t__ pch_set_station_address (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pch_dev*) ; 
 int /*<<< orphan*/  ptp_clock_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_pch_caps ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pch_dev*) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static s32
pch_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	s32 ret;
	unsigned long flags;
	struct pch_dev *chip;

	chip = kzalloc(sizeof(struct pch_dev), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	/* enable the 1588 pci device */
	ret = pci_enable_device(pdev);
	if (ret != 0) {
		dev_err(&pdev->dev, "could not enable the pci device\n");
		goto err_pci_en;
	}

	chip->mem_base = pci_resource_start(pdev, IO_MEM_BAR);
	if (!chip->mem_base) {
		dev_err(&pdev->dev, "could not locate IO memory address\n");
		ret = -ENODEV;
		goto err_pci_start;
	}

	/* retrieve the available length of the IO memory space */
	chip->mem_size = pci_resource_len(pdev, IO_MEM_BAR);

	/* allocate the memory for the device registers */
	if (!request_mem_region(chip->mem_base, chip->mem_size, "1588_regs")) {
		dev_err(&pdev->dev,
			"could not allocate register memory space\n");
		ret = -EBUSY;
		goto err_req_mem_region;
	}

	/* get the virtual address to the 1588 registers */
	chip->regs = ioremap(chip->mem_base, chip->mem_size);

	if (!chip->regs) {
		dev_err(&pdev->dev, "Could not get virtual address\n");
		ret = -ENOMEM;
		goto err_ioremap;
	}

	chip->caps = ptp_pch_caps;
	chip->ptp_clock = ptp_clock_register(&chip->caps, &pdev->dev);
	if (IS_ERR(chip->ptp_clock)) {
		ret = PTR_ERR(chip->ptp_clock);
		goto err_ptp_clock_reg;
	}

	spin_lock_init(&chip->register_lock);

	ret = request_irq(pdev->irq, &isr, IRQF_SHARED, KBUILD_MODNAME, chip);
	if (ret != 0) {
		dev_err(&pdev->dev, "failed to get irq %d\n", pdev->irq);
		goto err_req_irq;
	}

	/* indicate success */
	chip->irq = pdev->irq;
	chip->pdev = pdev;
	pci_set_drvdata(pdev, chip);

	spin_lock_irqsave(&chip->register_lock, flags);
	/* reset the ieee1588 h/w */
	pch_reset(chip);

	iowrite32(DEFAULT_ADDEND, &chip->regs->addend);
	iowrite32(1, &chip->regs->trgt_lo);
	iowrite32(0, &chip->regs->trgt_hi);
	iowrite32(PCH_TSE_TTIPEND, &chip->regs->event);

	pch_eth_enable_set(chip);

	if (strcmp(pch_param.station, "00:00:00:00:00:00") != 0) {
		if (pch_set_station_address(pch_param.station, pdev) != 0) {
			dev_err(&pdev->dev,
			"Invalid station address parameter\n"
			"Module loaded but station address not set correctly\n"
			);
		}
	}
	spin_unlock_irqrestore(&chip->register_lock, flags);
	return 0;

err_req_irq:
	ptp_clock_unregister(chip->ptp_clock);
err_ptp_clock_reg:
	iounmap(chip->regs);
	chip->regs = NULL;

err_ioremap:
	release_mem_region(chip->mem_base, chip->mem_size);

err_req_mem_region:
	chip->mem_base = 0;

err_pci_start:
	pci_disable_device(pdev);

err_pci_en:
	kfree(chip);
	dev_err(&pdev->dev, "probe failed(ret=0x%x)\n", ret);

	return ret;
}