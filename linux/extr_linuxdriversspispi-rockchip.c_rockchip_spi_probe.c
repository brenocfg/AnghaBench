#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int auto_runtime_pm; int mode_bits; int bits_per_word_mask; int /*<<< orphan*/ * dma_rx; int /*<<< orphan*/ * dma_tx; int /*<<< orphan*/  can_dma; int /*<<< orphan*/  flags; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  max_transfer_size; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  set_cs; TYPE_2__ dev; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ch; int /*<<< orphan*/  direction; void* addr; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ch; int /*<<< orphan*/  direction; void* addr; } ;
struct rockchip_spi {int /*<<< orphan*/ * apb_pclk; int /*<<< orphan*/ * spiclk; TYPE_3__ dma_tx; TYPE_1__ dma_rx; int /*<<< orphan*/  dma_caps; TYPE_4__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo_len; int /*<<< orphan*/  rsd_nsecs; int /*<<< orphan*/  max_freq; struct spi_master* master; int /*<<< orphan*/  type; int /*<<< orphan*/ * regs; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; int /*<<< orphan*/  id; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ROCKCHIP_SPI_MAX_CS_NUM ; 
 scalar_t__ ROCKCHIP_SPI_RXDR ; 
 scalar_t__ ROCKCHIP_SPI_TXDR ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int /*<<< orphan*/  SPI_MASTER_GPIO_SS ; 
 int /*<<< orphan*/  SSI_MOTO_SPI ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*) ; 
 void* devm_clk_get (TYPE_4__*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 int devm_spi_register_master (TYPE_4__*,struct spi_master*) ; 
 int /*<<< orphan*/  dma_get_slave_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 void* dma_request_chan (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  get_fifo_len (struct rockchip_spi*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_4__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_4__*) ; 
 int /*<<< orphan*/  rockchip_spi_can_dma ; 
 int /*<<< orphan*/  rockchip_spi_handle_err ; 
 int /*<<< orphan*/  rockchip_spi_max_transfer_size ; 
 int /*<<< orphan*/  rockchip_spi_prepare_message ; 
 int /*<<< orphan*/  rockchip_spi_set_cs ; 
 int /*<<< orphan*/  rockchip_spi_transfer_one ; 
 int /*<<< orphan*/  rockchip_spi_unprepare_message ; 
 struct spi_master* spi_alloc_master (TYPE_4__*,int) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int /*<<< orphan*/ ) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_spi_probe(struct platform_device *pdev)
{
	int ret;
	struct rockchip_spi *rs;
	struct spi_master *master;
	struct resource *mem;
	u32 rsd_nsecs;

	master = spi_alloc_master(&pdev->dev, sizeof(struct rockchip_spi));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	rs = spi_master_get_devdata(master);

	/* Get basic io resource and map it */
	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rs->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rs->regs)) {
		ret =  PTR_ERR(rs->regs);
		goto err_put_master;
	}

	rs->apb_pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	if (IS_ERR(rs->apb_pclk)) {
		dev_err(&pdev->dev, "Failed to get apb_pclk\n");
		ret = PTR_ERR(rs->apb_pclk);
		goto err_put_master;
	}

	rs->spiclk = devm_clk_get(&pdev->dev, "spiclk");
	if (IS_ERR(rs->spiclk)) {
		dev_err(&pdev->dev, "Failed to get spi_pclk\n");
		ret = PTR_ERR(rs->spiclk);
		goto err_put_master;
	}

	ret = clk_prepare_enable(rs->apb_pclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to enable apb_pclk\n");
		goto err_put_master;
	}

	ret = clk_prepare_enable(rs->spiclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to enable spi_clk\n");
		goto err_disable_apbclk;
	}

	spi_enable_chip(rs, 0);

	rs->type = SSI_MOTO_SPI;
	rs->master = master;
	rs->dev = &pdev->dev;
	rs->max_freq = clk_get_rate(rs->spiclk);

	if (!of_property_read_u32(pdev->dev.of_node, "rx-sample-delay-ns",
				  &rsd_nsecs))
		rs->rsd_nsecs = rsd_nsecs;

	rs->fifo_len = get_fifo_len(rs);
	if (!rs->fifo_len) {
		dev_err(&pdev->dev, "Failed to get fifo length\n");
		ret = -EINVAL;
		goto err_disable_spiclk;
	}

	spin_lock_init(&rs->lock);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	master->auto_runtime_pm = true;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP;
	master->num_chipselect = ROCKCHIP_SPI_MAX_CS_NUM;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(16) | SPI_BPW_MASK(8);

	master->set_cs = rockchip_spi_set_cs;
	master->prepare_message = rockchip_spi_prepare_message;
	master->unprepare_message = rockchip_spi_unprepare_message;
	master->transfer_one = rockchip_spi_transfer_one;
	master->max_transfer_size = rockchip_spi_max_transfer_size;
	master->handle_err = rockchip_spi_handle_err;
	master->flags = SPI_MASTER_GPIO_SS;

	rs->dma_tx.ch = dma_request_chan(rs->dev, "tx");
	if (IS_ERR(rs->dma_tx.ch)) {
		/* Check tx to see if we need defer probing driver */
		if (PTR_ERR(rs->dma_tx.ch) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto err_disable_pm_runtime;
		}
		dev_warn(rs->dev, "Failed to request TX DMA channel\n");
		rs->dma_tx.ch = NULL;
	}

	rs->dma_rx.ch = dma_request_chan(rs->dev, "rx");
	if (IS_ERR(rs->dma_rx.ch)) {
		if (PTR_ERR(rs->dma_rx.ch) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto err_free_dma_tx;
		}
		dev_warn(rs->dev, "Failed to request RX DMA channel\n");
		rs->dma_rx.ch = NULL;
	}

	if (rs->dma_tx.ch && rs->dma_rx.ch) {
		dma_get_slave_caps(rs->dma_rx.ch, &(rs->dma_caps));
		rs->dma_tx.addr = (dma_addr_t)(mem->start + ROCKCHIP_SPI_TXDR);
		rs->dma_rx.addr = (dma_addr_t)(mem->start + ROCKCHIP_SPI_RXDR);
		rs->dma_tx.direction = DMA_MEM_TO_DEV;
		rs->dma_rx.direction = DMA_DEV_TO_MEM;

		master->can_dma = rockchip_spi_can_dma;
		master->dma_tx = rs->dma_tx.ch;
		master->dma_rx = rs->dma_rx.ch;
	}

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register master\n");
		goto err_free_dma_rx;
	}

	return 0;

err_free_dma_rx:
	if (rs->dma_rx.ch)
		dma_release_channel(rs->dma_rx.ch);
err_free_dma_tx:
	if (rs->dma_tx.ch)
		dma_release_channel(rs->dma_tx.ch);
err_disable_pm_runtime:
	pm_runtime_disable(&pdev->dev);
err_disable_spiclk:
	clk_disable_unprepare(rs->spiclk);
err_disable_apbclk:
	clk_disable_unprepare(rs->apb_pclk);
err_put_master:
	spi_master_put(master);

	return ret;
}