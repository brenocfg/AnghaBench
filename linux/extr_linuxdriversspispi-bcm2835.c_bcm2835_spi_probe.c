#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int num_chipselect; TYPE_1__ dev; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  mode_bits; } ;
struct resource {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct bcm2835_spi {int irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CLEAR_RX ; 
 int BCM2835_SPI_CS_CLEAR_TX ; 
 int /*<<< orphan*/  BCM2835_SPI_MODE_BITS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int /*<<< orphan*/  bcm2835_dma_init (struct spi_master*,TYPE_2__*) ; 
 int /*<<< orphan*/  bcm2835_spi_handle_err ; 
 int /*<<< orphan*/  bcm2835_spi_interrupt ; 
 int /*<<< orphan*/  bcm2835_spi_prepare_message ; 
 int /*<<< orphan*/  bcm2835_spi_set_cs ; 
 int /*<<< orphan*/  bcm2835_spi_setup ; 
 int /*<<< orphan*/  bcm2835_spi_transfer_one ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int bcm2835_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct bcm2835_spi *bs;
	struct resource *res;
	int err;

	master = spi_alloc_master(&pdev->dev, sizeof(*bs));
	if (!master) {
		dev_err(&pdev->dev, "spi_alloc_master() failed\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, master);

	master->mode_bits = BCM2835_SPI_MODE_BITS;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->num_chipselect = 3;
	master->setup = bcm2835_spi_setup;
	master->set_cs = bcm2835_spi_set_cs;
	master->transfer_one = bcm2835_spi_transfer_one;
	master->handle_err = bcm2835_spi_handle_err;
	master->prepare_message = bcm2835_spi_prepare_message;
	master->dev.of_node = pdev->dev.of_node;

	bs = spi_master_get_devdata(master);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	bs->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(bs->regs)) {
		err = PTR_ERR(bs->regs);
		goto out_master_put;
	}

	bs->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(bs->clk)) {
		err = PTR_ERR(bs->clk);
		dev_err(&pdev->dev, "could not get clk: %d\n", err);
		goto out_master_put;
	}

	bs->irq = platform_get_irq(pdev, 0);
	if (bs->irq <= 0) {
		dev_err(&pdev->dev, "could not get IRQ: %d\n", bs->irq);
		err = bs->irq ? bs->irq : -ENODEV;
		goto out_master_put;
	}

	clk_prepare_enable(bs->clk);

	bcm2835_dma_init(master, &pdev->dev);

	/* initialise the hardware with the default polarities */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX);

	err = devm_request_irq(&pdev->dev, bs->irq, bcm2835_spi_interrupt, 0,
			       dev_name(&pdev->dev), master);
	if (err) {
		dev_err(&pdev->dev, "could not request IRQ: %d\n", err);
		goto out_clk_disable;
	}

	err = devm_spi_register_master(&pdev->dev, master);
	if (err) {
		dev_err(&pdev->dev, "could not register SPI master: %d\n", err);
		goto out_clk_disable;
	}

	return 0;

out_clk_disable:
	clk_disable_unprepare(bs->clk);
out_master_put:
	spi_master_put(master);
	return err;
}