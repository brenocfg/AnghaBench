#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; TYPE_3__ dummy_controller; TYPE_2__ ecc; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  dev_ready; } ;
struct TYPE_9__ {TYPE_4__* parent; } ;
struct mtd_info {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  owner; } ;
struct ar934x_nfc {scalar_t__ irq; struct nand_chip nand_chip; int /*<<< orphan*/  swap_dma; TYPE_4__* parent; int /*<<< orphan*/  rst; int /*<<< orphan*/  irq_waitq; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR934X_NFC_DRIVER_NAME ; 
 int /*<<< orphan*/  AR934X_NFC_ID_BUF_SIZE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int ar934x_nfc_alloc_buf (struct ar934x_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_cmd_ctrl ; 
 int /*<<< orphan*/  ar934x_nfc_cmdfunc ; 
 int /*<<< orphan*/  ar934x_nfc_controller_ops ; 
 int /*<<< orphan*/  ar934x_nfc_dev_ready ; 
 int /*<<< orphan*/  ar934x_nfc_dma_mask ; 
 int /*<<< orphan*/  ar934x_nfc_free_buf (struct ar934x_nfc*) ; 
 int ar934x_nfc_hw_init (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_irq_handler ; 
 int /*<<< orphan*/  ar934x_nfc_read_buf ; 
 int /*<<< orphan*/  ar934x_nfc_read_byte ; 
 int /*<<< orphan*/  ar934x_nfc_write_buf ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct ar934x_nfc* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar934x_nfc*) ; 
 int /*<<< orphan*/  devm_reset_control_get (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct ar934x_nfc*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ar934x_nfc*) ; 

__attribute__((used)) static int ar934x_nfc_probe(struct platform_device *pdev)
{
	struct ar934x_nfc *nfc;
	struct resource *res;
	struct mtd_info *mtd;
	struct nand_chip *nand;
	int ret;

	pdev->dev.dma_mask = &ar934x_nfc_dma_mask;
	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		return -EINVAL;
	}

	nfc = devm_kzalloc(&pdev->dev, sizeof(struct ar934x_nfc), GFP_KERNEL);
	if (!nfc) {
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		return -ENOMEM;
	}

	nfc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(nfc->base)) {
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		return PTR_ERR(nfc->base);
	}

	nfc->irq = platform_get_irq(pdev, 0);
	if (nfc->irq < 0) {
		dev_err(&pdev->dev, "no IRQ resource specified\n");
		return -EINVAL;
	}

	init_waitqueue_head(&nfc->irq_waitq);
	ret = devm_request_irq(&pdev->dev, nfc->irq, ar934x_nfc_irq_handler,
			       0, AR934X_NFC_DRIVER_NAME, nfc);
	if (ret) {
		dev_err(&pdev->dev, "devm_request_irq failed, err:%d\n", ret);
		return ret;
	}

	nfc->rst = devm_reset_control_get(&pdev->dev, "nand");
	if (IS_ERR(nfc->rst)) {
		dev_err(&pdev->dev, "Failed to get reset\n");
		return PTR_ERR(nfc->rst);
	}

	nfc->parent = &pdev->dev;
	nfc->swap_dma = of_property_read_bool(pdev->dev.of_node,
					      "qca,nand-swap-dma");

	nand = &nfc->nand_chip;
	mtd = nand_to_mtd(nand);

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &pdev->dev;
	mtd->name = AR934X_NFC_DRIVER_NAME;

	nand_set_controller_data(nand, nfc);
	nand_set_flash_node(nand, pdev->dev.of_node);
	nand->chip_delay = 25;
	nand->dev_ready = ar934x_nfc_dev_ready;
	nand->cmdfunc = ar934x_nfc_cmdfunc;
	nand->cmd_ctrl = ar934x_nfc_cmd_ctrl;	/* dummy */
	nand->read_byte = ar934x_nfc_read_byte;
	nand->write_buf = ar934x_nfc_write_buf;
	nand->read_buf = ar934x_nfc_read_buf;
	nand->ecc.mode = NAND_ECC_HW;	/* default */
	platform_set_drvdata(pdev, nfc);

	ret = ar934x_nfc_alloc_buf(nfc, AR934X_NFC_ID_BUF_SIZE);
	if (ret)
		return ret;

	ret = ar934x_nfc_hw_init(nfc);
	if (ret) {
		dev_err(&pdev->dev, "hardware init failed, err:%d\n", ret);
		goto err_free_buf;
	}

	nand->dummy_controller.ops = &ar934x_nfc_controller_ops;
	ret = nand_scan(mtd, 1);
	if (ret) {
		dev_err(&pdev->dev, "nand_scan failed, err:%d\n", ret);
		goto err_free_buf;
	}

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(&pdev->dev, "unable to register mtd, err:%d\n", ret);
		goto err_free_buf;
	}

	return 0;

err_free_buf:
	ar934x_nfc_free_buf(nfc);
	return ret;
}