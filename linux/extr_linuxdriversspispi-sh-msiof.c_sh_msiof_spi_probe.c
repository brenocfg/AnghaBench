#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int auto_runtime_pm; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  slave_abort; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  setup; TYPE_2__ dev; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_chipselect; } ;
struct sh_msiof_spi_priv {struct sh_msiof_spi_info* info; scalar_t__ rx_fifo_size; scalar_t__ tx_fifo_size; struct platform_device* pdev; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  clk; int /*<<< orphan*/  done_txdma; int /*<<< orphan*/  done; int /*<<< orphan*/  min_div_pow; struct spi_master* master; } ;
struct sh_msiof_spi_info {scalar_t__ mode; int /*<<< orphan*/  num_chipselect; scalar_t__ rx_fifo_override; scalar_t__ tx_fifo_override; } ;
struct sh_msiof_chipdata {int /*<<< orphan*/  master_flags; scalar_t__ rx_fifo_size; scalar_t__ tx_fifo_size; int /*<<< orphan*/  min_div_pow; } ;
struct resource {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; TYPE_1__* id_entry; } ;
struct TYPE_17__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MSIOF_SPI_SLAVE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_3WIRE ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct sh_msiof_spi_info* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sh_msiof_spi_priv*) ; 
 int devm_spi_register_master (TYPE_3__*,struct spi_master*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct sh_msiof_chipdata* of_device_get_match_data (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int sh_msiof_get_cs_gpios (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_prepare_message ; 
 int /*<<< orphan*/  sh_msiof_release_dma (struct sh_msiof_spi_priv*) ; 
 int sh_msiof_request_dma (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_slave_abort ; 
 int /*<<< orphan*/  sh_msiof_spi_irq ; 
 struct sh_msiof_spi_info* sh_msiof_spi_parse_dt (TYPE_3__*) ; 
 int /*<<< orphan*/  sh_msiof_spi_setup ; 
 int /*<<< orphan*/  sh_msiof_transfer_one ; 
 struct spi_master* spi_alloc_master (TYPE_3__*,int) ; 
 struct spi_master* spi_alloc_slave (TYPE_3__*,int) ; 
 struct sh_msiof_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int sh_msiof_spi_probe(struct platform_device *pdev)
{
	struct resource	*r;
	struct spi_master *master;
	const struct sh_msiof_chipdata *chipdata;
	struct sh_msiof_spi_info *info;
	struct sh_msiof_spi_priv *p;
	int i;
	int ret;

	chipdata = of_device_get_match_data(&pdev->dev);
	if (chipdata) {
		info = sh_msiof_spi_parse_dt(&pdev->dev);
	} else {
		chipdata = (const void *)pdev->id_entry->driver_data;
		info = dev_get_platdata(&pdev->dev);
	}

	if (!info) {
		dev_err(&pdev->dev, "failed to obtain device info\n");
		return -ENXIO;
	}

	if (info->mode == MSIOF_SPI_SLAVE)
		master = spi_alloc_slave(&pdev->dev,
					 sizeof(struct sh_msiof_spi_priv));
	else
		master = spi_alloc_master(&pdev->dev,
					  sizeof(struct sh_msiof_spi_priv));
	if (master == NULL)
		return -ENOMEM;

	p = spi_master_get_devdata(master);

	platform_set_drvdata(pdev, p);
	p->master = master;
	p->info = info;
	p->min_div_pow = chipdata->min_div_pow;

	init_completion(&p->done);
	init_completion(&p->done_txdma);

	p->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(p->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = PTR_ERR(p->clk);
		goto err1;
	}

	i = platform_get_irq(pdev, 0);
	if (i < 0) {
		dev_err(&pdev->dev, "cannot get platform IRQ\n");
		ret = -ENOENT;
		goto err1;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	p->mapbase = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(p->mapbase)) {
		ret = PTR_ERR(p->mapbase);
		goto err1;
	}

	ret = devm_request_irq(&pdev->dev, i, sh_msiof_spi_irq, 0,
			       dev_name(&pdev->dev), p);
	if (ret) {
		dev_err(&pdev->dev, "unable to request irq\n");
		goto err1;
	}

	p->pdev = pdev;
	pm_runtime_enable(&pdev->dev);

	/* Platform data may override FIFO sizes */
	p->tx_fifo_size = chipdata->tx_fifo_size;
	p->rx_fifo_size = chipdata->rx_fifo_size;
	if (p->info->tx_fifo_override)
		p->tx_fifo_size = p->info->tx_fifo_override;
	if (p->info->rx_fifo_override)
		p->rx_fifo_size = p->info->rx_fifo_override;

	/* Setup GPIO chip selects */
	master->num_chipselect = p->info->num_chipselect;
	ret = sh_msiof_get_cs_gpios(p);
	if (ret)
		goto err1;

	/* init master code */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->mode_bits |= SPI_LSB_FIRST | SPI_3WIRE;
	master->flags = chipdata->master_flags;
	master->bus_num = pdev->id;
	master->dev.of_node = pdev->dev.of_node;
	master->setup = sh_msiof_spi_setup;
	master->prepare_message = sh_msiof_prepare_message;
	master->slave_abort = sh_msiof_slave_abort;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 32);
	master->auto_runtime_pm = true;
	master->transfer_one = sh_msiof_transfer_one;

	ret = sh_msiof_request_dma(p);
	if (ret < 0)
		dev_warn(&pdev->dev, "DMA not available, using PIO\n");

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "spi_register_master error.\n");
		goto err2;
	}

	return 0;

 err2:
	sh_msiof_release_dma(p);
	pm_runtime_disable(&pdev->dev);
 err1:
	spi_master_put(master);
	return ret;
}