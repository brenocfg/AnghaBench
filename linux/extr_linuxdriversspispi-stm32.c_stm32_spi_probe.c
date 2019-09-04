#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct stm32_spi {scalar_t__ irq; int clk_rate; int /*<<< orphan*/  clk; void* dma_rx; void* dma_tx; TYPE_2__* dev; int /*<<< orphan*/  fifo_size; int /*<<< orphan*/  rst; scalar_t__ phys_addr; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; struct spi_master* master; } ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int auto_runtime_pm; int mode_bits; int max_speed_hz; int min_speed_hz; int* cs_gpios; int num_chipselect; int /*<<< orphan*/  can_dma; void* dma_rx; void* dma_tx; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  bus_num; TYPE_1__ dev; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_3WIRE ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 int SPI_MBR_DIV_MAX ; 
 int SPI_MBR_DIV_MIN ; 
 int SPI_MODE_3 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int devm_gpio_request (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_request_threaded_irq (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_spi_can_dma ; 
 int stm32_spi_config (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_get_bpw_mask (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_get_fifo_size (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_irq ; 
 int /*<<< orphan*/  stm32_spi_prepare_msg ; 
 int /*<<< orphan*/  stm32_spi_setup ; 
 int /*<<< orphan*/  stm32_spi_transfer_one ; 
 int /*<<< orphan*/  stm32_spi_unprepare_msg ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct stm32_spi *spi;
	struct resource *res;
	int i, ret;

	master = spi_alloc_master(&pdev->dev, sizeof(struct stm32_spi));
	if (!master) {
		dev_err(&pdev->dev, "spi master allocation failed\n");
		return -ENOMEM;
	}
	platform_set_drvdata(pdev, master);

	spi = spi_master_get_devdata(master);
	spi->dev = &pdev->dev;
	spi->master = master;
	spin_lock_init(&spi->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	spi->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(spi->base)) {
		ret = PTR_ERR(spi->base);
		goto err_master_put;
	}
	spi->phys_addr = (dma_addr_t)res->start;

	spi->irq = platform_get_irq(pdev, 0);
	if (spi->irq <= 0) {
		dev_err(&pdev->dev, "no irq: %d\n", spi->irq);
		ret = -ENOENT;
		goto err_master_put;
	}
	ret = devm_request_threaded_irq(&pdev->dev, spi->irq, NULL,
					stm32_spi_irq, IRQF_ONESHOT,
					pdev->name, master);
	if (ret) {
		dev_err(&pdev->dev, "irq%d request failed: %d\n", spi->irq,
			ret);
		goto err_master_put;
	}

	spi->clk = devm_clk_get(&pdev->dev, 0);
	if (IS_ERR(spi->clk)) {
		ret = PTR_ERR(spi->clk);
		dev_err(&pdev->dev, "clk get failed: %d\n", ret);
		goto err_master_put;
	}

	ret = clk_prepare_enable(spi->clk);
	if (ret) {
		dev_err(&pdev->dev, "clk enable failed: %d\n", ret);
		goto err_master_put;
	}
	spi->clk_rate = clk_get_rate(spi->clk);
	if (!spi->clk_rate) {
		dev_err(&pdev->dev, "clk rate = 0\n");
		ret = -EINVAL;
		goto err_clk_disable;
	}

	spi->rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (!IS_ERR(spi->rst)) {
		reset_control_assert(spi->rst);
		udelay(2);
		reset_control_deassert(spi->rst);
	}

	spi->fifo_size = stm32_spi_get_fifo_size(spi);

	ret = stm32_spi_config(spi);
	if (ret) {
		dev_err(&pdev->dev, "controller configuration failed: %d\n",
			ret);
		goto err_clk_disable;
	}

	master->dev.of_node = pdev->dev.of_node;
	master->auto_runtime_pm = true;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_MODE_3 | SPI_CS_HIGH | SPI_LSB_FIRST |
			    SPI_3WIRE | SPI_LOOP;
	master->bits_per_word_mask = stm32_spi_get_bpw_mask(spi);
	master->max_speed_hz = spi->clk_rate / SPI_MBR_DIV_MIN;
	master->min_speed_hz = spi->clk_rate / SPI_MBR_DIV_MAX;
	master->setup = stm32_spi_setup;
	master->prepare_message = stm32_spi_prepare_msg;
	master->transfer_one = stm32_spi_transfer_one;
	master->unprepare_message = stm32_spi_unprepare_msg;

	spi->dma_tx = dma_request_slave_channel(spi->dev, "tx");
	if (!spi->dma_tx)
		dev_warn(&pdev->dev, "failed to request tx dma channel\n");
	else
		master->dma_tx = spi->dma_tx;

	spi->dma_rx = dma_request_slave_channel(spi->dev, "rx");
	if (!spi->dma_rx)
		dev_warn(&pdev->dev, "failed to request rx dma channel\n");
	else
		master->dma_rx = spi->dma_rx;

	if (spi->dma_tx || spi->dma_rx)
		master->can_dma = stm32_spi_can_dma;

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret) {
		dev_err(&pdev->dev, "spi master registration failed: %d\n",
			ret);
		goto err_dma_release;
	}

	if (!master->cs_gpios) {
		dev_err(&pdev->dev, "no CS gpios available\n");
		ret = -EINVAL;
		goto err_dma_release;
	}

	for (i = 0; i < master->num_chipselect; i++) {
		if (!gpio_is_valid(master->cs_gpios[i])) {
			dev_err(&pdev->dev, "%i is not a valid gpio\n",
				master->cs_gpios[i]);
			ret = -EINVAL;
			goto err_dma_release;
		}

		ret = devm_gpio_request(&pdev->dev, master->cs_gpios[i],
					DRIVER_NAME);
		if (ret) {
			dev_err(&pdev->dev, "can't get CS gpio %i\n",
				master->cs_gpios[i]);
			goto err_dma_release;
		}
	}

	dev_info(&pdev->dev, "driver initialized\n");

	return 0;

err_dma_release:
	if (spi->dma_tx)
		dma_release_channel(spi->dma_tx);
	if (spi->dma_rx)
		dma_release_channel(spi->dma_rx);

	pm_runtime_disable(&pdev->dev);
err_clk_disable:
	clk_disable_unprepare(spi->clk);
err_master_put:
	spi_master_put(master);

	return ret;
}