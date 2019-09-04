#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int flags; int /*<<< orphan*/  bus_num; TYPE_1__ dev; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_transfer_hardware; int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  bits_per_word_mask; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct fsl_lpspi_data {int txfifosize; int rxfifosize; scalar_t__ clk; scalar_t__ base; int /*<<< orphan*/  xfer_done; TYPE_2__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IMX7ULP_PARAM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_MASTER_MUST_RX ; 
 int SPI_MASTER_MUST_TX ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 scalar_t__ devm_clk_get (TYPE_2__*,char*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsl_lpspi_data*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  fsl_lpspi_isr ; 
 int /*<<< orphan*/  fsl_lpspi_transfer_one_msg ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpspi_prepare_xfer_hardware ; 
 int /*<<< orphan*/  lpspi_unprepare_xfer_hardware ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int readl (scalar_t__) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct fsl_lpspi_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int fsl_lpspi_probe(struct platform_device *pdev)
{
	struct fsl_lpspi_data *fsl_lpspi;
	struct spi_master *master;
	struct resource *res;
	int ret, irq;
	u32 temp;

	master = spi_alloc_master(&pdev->dev, sizeof(struct fsl_lpspi_data));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 32);
	master->bus_num = pdev->id;

	fsl_lpspi = spi_master_get_devdata(master);
	fsl_lpspi->dev = &pdev->dev;

	master->transfer_one_message = fsl_lpspi_transfer_one_msg;
	master->prepare_transfer_hardware = lpspi_prepare_xfer_hardware;
	master->unprepare_transfer_hardware = lpspi_unprepare_xfer_hardware;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->flags = SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;

	init_completion(&fsl_lpspi->xfer_done);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fsl_lpspi->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(fsl_lpspi->base)) {
		ret = PTR_ERR(fsl_lpspi->base);
		goto out_master_put;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto out_master_put;
	}

	ret = devm_request_irq(&pdev->dev, irq, fsl_lpspi_isr, 0,
			       dev_name(&pdev->dev), fsl_lpspi);
	if (ret) {
		dev_err(&pdev->dev, "can't get irq%d: %d\n", irq, ret);
		goto out_master_put;
	}

	fsl_lpspi->clk = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(fsl_lpspi->clk)) {
		ret = PTR_ERR(fsl_lpspi->clk);
		goto out_master_put;
	}

	ret = clk_prepare_enable(fsl_lpspi->clk);
	if (ret) {
		dev_err(&pdev->dev, "can't enable lpspi clock, ret=%d\n", ret);
		goto out_master_put;
	}

	temp = readl(fsl_lpspi->base + IMX7ULP_PARAM);
	fsl_lpspi->txfifosize = 1 << (temp & 0x0f);
	fsl_lpspi->rxfifosize = 1 << ((temp >> 8) & 0x0f);

	clk_disable_unprepare(fsl_lpspi->clk);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "spi_register_master error.\n");
		goto out_master_put;
	}

	return 0;

out_master_put:
	spi_master_put(master);

	return ret;
}