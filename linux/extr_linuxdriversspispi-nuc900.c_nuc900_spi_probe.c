#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int mode_bits; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  num_chipselect; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  txrx_bufs; int /*<<< orphan*/  chipselect; struct spi_master* master; } ;
struct nuc900_spi {scalar_t__ irq; struct spi_master* master; int /*<<< orphan*/  clk; TYPE_1__ bitbang; int /*<<< orphan*/  regs; TYPE_2__* pdata; int /*<<< orphan*/  done; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_num; int /*<<< orphan*/  num_cs; scalar_t__ lsb; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nuc900_spi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfp_set_groupg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nuc900_init_spi (struct nuc900_spi*) ; 
 int /*<<< orphan*/  nuc900_spi_chipsel ; 
 int /*<<< orphan*/  nuc900_spi_irq ; 
 int /*<<< orphan*/  nuc900_spi_txrx ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nuc900_spi*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 int spi_bitbang_start (TYPE_1__*) ; 
 struct nuc900_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int nuc900_spi_probe(struct platform_device *pdev)
{
	struct nuc900_spi *hw;
	struct spi_master *master;
	struct resource *res;
	int err = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(struct nuc900_spi));
	if (master == NULL) {
		dev_err(&pdev->dev, "No memory for spi_master\n");
		return -ENOMEM;
	}

	hw = spi_master_get_devdata(master);
	hw->master = master;
	hw->pdata  = dev_get_platdata(&pdev->dev);

	if (hw->pdata == NULL) {
		dev_err(&pdev->dev, "No platform data supplied\n");
		err = -ENOENT;
		goto err_pdata;
	}

	platform_set_drvdata(pdev, hw);
	init_completion(&hw->done);

	master->mode_bits          = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	if (hw->pdata->lsb)
		master->mode_bits |= SPI_LSB_FIRST;
	master->num_chipselect     = hw->pdata->num_cs;
	master->bus_num            = hw->pdata->bus_num;
	hw->bitbang.master         = hw->master;
	hw->bitbang.chipselect     = nuc900_spi_chipsel;
	hw->bitbang.txrx_bufs      = nuc900_spi_txrx;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hw->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hw->regs)) {
		err = PTR_ERR(hw->regs);
		goto err_pdata;
	}

	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq < 0) {
		dev_err(&pdev->dev, "No IRQ specified\n");
		err = -ENOENT;
		goto err_pdata;
	}

	err = devm_request_irq(&pdev->dev, hw->irq, nuc900_spi_irq, 0,
				pdev->name, hw);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_pdata;
	}

	hw->clk = devm_clk_get(&pdev->dev, "spi");
	if (IS_ERR(hw->clk)) {
		dev_err(&pdev->dev, "No clock for device\n");
		err = PTR_ERR(hw->clk);
		goto err_pdata;
	}

	mfp_set_groupg(&pdev->dev, NULL);
	nuc900_init_spi(hw);

	err = spi_bitbang_start(&hw->bitbang);
	if (err) {
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		goto err_register;
	}

	return 0;

err_register:
	clk_disable(hw->clk);
err_pdata:
	spi_master_put(hw->master);
	return err;
}