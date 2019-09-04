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
struct uio_info {char* name; char* version; scalar_t__ priv; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; TYPE_1__* port; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  porttype; int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INTA_DRVR_ADDR ; 
 int INTA_ENABLED_FLAG ; 
 int /*<<< orphan*/  INT_ENABLE ; 
 scalar_t__ INT_ENABLE_ADDR ; 
 scalar_t__ INT_MASK_ADDR ; 
 int /*<<< orphan*/  INT_MASK_ALL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  UIO_PORT_GPIO ; 
 int /*<<< orphan*/  aectc_irq ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 struct uio_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct uio_info*) ; 
 int /*<<< orphan*/  print_board_data (struct pci_dev*,struct uio_info*) ; 
 int uio_register_device (int /*<<< orphan*/ *,struct uio_info*) ; 

__attribute__((used)) static int probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct uio_info *info;
	int ret;

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if (pci_enable_device(pdev))
		goto out_free;

	if (pci_request_regions(pdev, "aectc"))
		goto out_disable;

	info->name = "aectc";
	info->port[0].start = pci_resource_start(pdev, 0);
	if (!info->port[0].start)
		goto out_release;
	info->priv = pci_iomap(pdev, 0, 0);
	if (!info->priv)
		goto out_release;
	info->port[0].size = pci_resource_len(pdev, 0);
	info->port[0].porttype = UIO_PORT_GPIO;

	info->version = "0.0.1";
	info->irq = pdev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = aectc_irq;

	print_board_data(pdev, info);
	ret = uio_register_device(&pdev->dev, info);
	if (ret)
		goto out_unmap;

	iowrite32(INT_ENABLE, info->priv + INT_ENABLE_ADDR);
	iowrite8(INT_MASK_ALL, info->priv + INT_MASK_ADDR);
	if (!(ioread8(info->priv + INTA_DRVR_ADDR)
			& INTA_ENABLED_FLAG))
		dev_err(&pdev->dev, "aectc: interrupts not enabled\n");

	pci_set_drvdata(pdev, info);

	return 0;

out_unmap:
	pci_iounmap(pdev, info->priv);
out_release:
	pci_release_regions(pdev);
out_disable:
	pci_disable_device(pdev);
out_free:
	kfree(info);
	return -ENODEV;
}