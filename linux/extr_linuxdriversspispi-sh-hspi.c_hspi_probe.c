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
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int auto_runtime_pm; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  transfer_one_message; TYPE_1__ dev; int /*<<< orphan*/  bus_num; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct hspi_priv {int /*<<< orphan*/  addr; TYPE_2__* dev; struct clk* clk; struct spi_master* master; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 struct clk* clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  hspi_transfer_one_message ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hspi_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct hspi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int hspi_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct spi_master *master;
	struct hspi_priv *hspi;
	struct clk *clk;
	int ret;

	/* get base addr */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "invalid resource\n");
		return -EINVAL;
	}

	master = spi_alloc_master(&pdev->dev, sizeof(*hspi));
	if (!master) {
		dev_err(&pdev->dev, "spi_alloc_master error.\n");
		return -ENOMEM;
	}

	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "couldn't get clock\n");
		ret = -EINVAL;
		goto error0;
	}

	hspi = spi_master_get_devdata(master);
	platform_set_drvdata(pdev, hspi);

	/* init hspi */
	hspi->master	= master;
	hspi->dev	= &pdev->dev;
	hspi->clk	= clk;
	hspi->addr	= devm_ioremap(hspi->dev,
				       res->start, resource_size(res));
	if (!hspi->addr) {
		dev_err(&pdev->dev, "ioremap error.\n");
		ret = -ENOMEM;
		goto error1;
	}

	pm_runtime_enable(&pdev->dev);

	master->bus_num		= pdev->id;
	master->mode_bits	= SPI_CPOL | SPI_CPHA;
	master->dev.of_node	= pdev->dev.of_node;
	master->auto_runtime_pm = true;
	master->transfer_one_message		= hspi_transfer_one_message;
	master->bits_per_word_mask = SPI_BPW_MASK(8);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "spi_register_master error.\n");
		goto error2;
	}

	return 0;

 error2:
	pm_runtime_disable(&pdev->dev);
 error1:
	clk_put(clk);
 error0:
	spi_master_put(master);

	return ret;
}