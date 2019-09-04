#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {scalar_t__ of_node; } ;
struct spi_master {int bus_num; int mode_bits; int num_chipselect; TYPE_3__ dev; int /*<<< orphan*/  cleanup; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  setup; } ;
struct resource {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct bcm_qspi_soc_intc {int /*<<< orphan*/  (* bcm_qspi_int_set ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ;} ;
struct bcm_qspi_dev_id {int dummy; } ;
struct TYPE_9__ {int width; int addrlen; int hp; } ;
struct TYPE_10__ {int mspi_last_trans; scalar_t__ byte; int /*<<< orphan*/ * trans; } ;
struct bcm_qspi {int bspi_mode; int base_clk; int max_speed_hz; int curr_cs; TYPE_5__* dev_ids; void* clk; TYPE_1__ xfer_mode; int /*<<< orphan*/  bspi_done; int /*<<< orphan*/  mspi_done; struct bcm_qspi_soc_intc* soc_intc; void** base; int /*<<< orphan*/  big_endian; struct spi_master* master; TYPE_2__ trans_pos; struct platform_device* pdev; } ;
struct TYPE_13__ {TYPE_4__* irqp; struct bcm_qspi* dev; } ;
struct TYPE_12__ {char* irq_name; scalar_t__ irq_source; int /*<<< orphan*/  irq_handler; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 size_t BSPI ; 
 size_t CHIP_SELECT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 size_t MSPI ; 
 int /*<<< orphan*/  MSPI_DONE ; 
 int NUM_CHIPSELECT ; 
 int PTR_ERR (void*) ; 
 int QSPI_SPBR_MIN ; 
 scalar_t__ SINGLE_L2 ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int /*<<< orphan*/  bcm_qspi_cleanup ; 
 int /*<<< orphan*/  bcm_qspi_hw_init (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_hw_uninit (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_mem_ops ; 
 int /*<<< orphan*/  bcm_qspi_of_match ; 
 int /*<<< orphan*/  bcm_qspi_setup ; 
 int /*<<< orphan*/  bcm_qspi_transfer_one ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_5__*) ; 
 int devm_spi_register_master (struct device*,struct spi_master*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_5__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  of_device_is_big_endian (scalar_t__) ; 
 int /*<<< orphan*/  of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_qspi*) ; 
 TYPE_4__* qspi_irq_tab ; 
 struct spi_master* spi_alloc_master (struct device*,int) ; 
 struct bcm_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  stub1 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ; 

int bcm_qspi_probe(struct platform_device *pdev,
		   struct bcm_qspi_soc_intc *soc_intc)
{
	struct device *dev = &pdev->dev;
	struct bcm_qspi *qspi;
	struct spi_master *master;
	struct resource *res;
	int irq, ret = 0, num_ints = 0;
	u32 val;
	const char *name = NULL;
	int num_irqs = ARRAY_SIZE(qspi_irq_tab);

	/* We only support device-tree instantiation */
	if (!dev->of_node)
		return -ENODEV;

	if (!of_match_node(bcm_qspi_of_match, dev->of_node))
		return -ENODEV;

	master = spi_alloc_master(dev, sizeof(struct bcm_qspi));
	if (!master) {
		dev_err(dev, "error allocating spi_master\n");
		return -ENOMEM;
	}

	qspi = spi_master_get_devdata(master);
	qspi->pdev = pdev;
	qspi->trans_pos.trans = NULL;
	qspi->trans_pos.byte = 0;
	qspi->trans_pos.mspi_last_trans = true;
	qspi->master = master;

	master->bus_num = -1;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_RX_DUAL | SPI_RX_QUAD;
	master->setup = bcm_qspi_setup;
	master->transfer_one = bcm_qspi_transfer_one;
	master->mem_ops = &bcm_qspi_mem_ops;
	master->cleanup = bcm_qspi_cleanup;
	master->dev.of_node = dev->of_node;
	master->num_chipselect = NUM_CHIPSELECT;

	qspi->big_endian = of_device_is_big_endian(dev->of_node);

	if (!of_property_read_u32(dev->of_node, "num-cs", &val))
		master->num_chipselect = val;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "hif_mspi");
	if (!res)
		res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						   "mspi");

	if (res) {
		qspi->base[MSPI]  = devm_ioremap_resource(dev, res);
		if (IS_ERR(qspi->base[MSPI])) {
			ret = PTR_ERR(qspi->base[MSPI]);
			goto qspi_resource_err;
		}
	} else {
		goto qspi_resource_err;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "bspi");
	if (res) {
		qspi->base[BSPI]  = devm_ioremap_resource(dev, res);
		if (IS_ERR(qspi->base[BSPI])) {
			ret = PTR_ERR(qspi->base[BSPI]);
			goto qspi_resource_err;
		}
		qspi->bspi_mode = true;
	} else {
		qspi->bspi_mode = false;
	}

	dev_info(dev, "using %smspi mode\n", qspi->bspi_mode ? "bspi-" : "");

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cs_reg");
	if (res) {
		qspi->base[CHIP_SELECT]  = devm_ioremap_resource(dev, res);
		if (IS_ERR(qspi->base[CHIP_SELECT])) {
			ret = PTR_ERR(qspi->base[CHIP_SELECT]);
			goto qspi_resource_err;
		}
	}

	qspi->dev_ids = kcalloc(num_irqs, sizeof(struct bcm_qspi_dev_id),
				GFP_KERNEL);
	if (!qspi->dev_ids) {
		ret = -ENOMEM;
		goto qspi_resource_err;
	}

	for (val = 0; val < num_irqs; val++) {
		irq = -1;
		name = qspi_irq_tab[val].irq_name;
		if (qspi_irq_tab[val].irq_source == SINGLE_L2) {
			/* get the l2 interrupts */
			irq = platform_get_irq_byname(pdev, name);
		} else if (!num_ints && soc_intc) {
			/* all mspi, bspi intrs muxed to one L1 intr */
			irq = platform_get_irq(pdev, 0);
		}

		if (irq  >= 0) {
			ret = devm_request_irq(&pdev->dev, irq,
					       qspi_irq_tab[val].irq_handler, 0,
					       name,
					       &qspi->dev_ids[val]);
			if (ret < 0) {
				dev_err(&pdev->dev, "IRQ %s not found\n", name);
				goto qspi_probe_err;
			}

			qspi->dev_ids[val].dev = qspi;
			qspi->dev_ids[val].irqp = &qspi_irq_tab[val];
			num_ints++;
			dev_dbg(&pdev->dev, "registered IRQ %s %d\n",
				qspi_irq_tab[val].irq_name,
				irq);
		}
	}

	if (!num_ints) {
		dev_err(&pdev->dev, "no IRQs registered, cannot init driver\n");
		ret = -EINVAL;
		goto qspi_probe_err;
	}

	/*
	 * Some SoCs integrate spi controller (e.g., its interrupt bits)
	 * in specific ways
	 */
	if (soc_intc) {
		qspi->soc_intc = soc_intc;
		soc_intc->bcm_qspi_int_set(soc_intc, MSPI_DONE, true);
	} else {
		qspi->soc_intc = NULL;
	}

	qspi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(qspi->clk)) {
		dev_warn(dev, "unable to get clock\n");
		ret = PTR_ERR(qspi->clk);
		goto qspi_probe_err;
	}

	ret = clk_prepare_enable(qspi->clk);
	if (ret) {
		dev_err(dev, "failed to prepare clock\n");
		goto qspi_probe_err;
	}

	qspi->base_clk = clk_get_rate(qspi->clk);
	qspi->max_speed_hz = qspi->base_clk / (QSPI_SPBR_MIN * 2);

	bcm_qspi_hw_init(qspi);
	init_completion(&qspi->mspi_done);
	init_completion(&qspi->bspi_done);
	qspi->curr_cs = -1;

	platform_set_drvdata(pdev, qspi);

	qspi->xfer_mode.width = -1;
	qspi->xfer_mode.addrlen = -1;
	qspi->xfer_mode.hp = -1;

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(dev, "can't register master\n");
		goto qspi_reg_err;
	}

	return 0;

qspi_reg_err:
	bcm_qspi_hw_uninit(qspi);
	clk_disable_unprepare(qspi->clk);
qspi_probe_err:
	kfree(qspi->dev_ids);
qspi_resource_err:
	spi_master_put(master);
	return ret;
}