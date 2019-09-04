#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; TYPE_1__ dev; } ;
struct resource {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct ath79_spi_platform_data {int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;
struct TYPE_10__ {struct spi_master* master; int /*<<< orphan*/  flags; int /*<<< orphan*/  setup_transfer; int /*<<< orphan*/ * txrx_word; int /*<<< orphan*/  chipselect; } ;
struct ath79_spi {unsigned long rrw_delay; TYPE_2__ bitbang; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned long ATH79_SPI_RRW_DELAY_FACTOR ; 
 unsigned long DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MHZ ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int /*<<< orphan*/  SPI_CS_HIGH ; 
 size_t SPI_MODE_0 ; 
 int /*<<< orphan*/  ath79_spi_chipselect ; 
 int /*<<< orphan*/  ath79_spi_cleanup ; 
 int /*<<< orphan*/  ath79_spi_disable (struct ath79_spi*) ; 
 int /*<<< orphan*/  ath79_spi_enable (struct ath79_spi*) ; 
 int /*<<< orphan*/  ath79_spi_setup ; 
 int /*<<< orphan*/  ath79_spi_txrx_mode0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct ath79_spi_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ath79_spi*) ; 
 struct spi_master* spi_alloc_master (TYPE_3__*,int) ; 
 int /*<<< orphan*/  spi_bitbang_setup_transfer ; 
 int spi_bitbang_start (TYPE_2__*) ; 
 struct ath79_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int ath79_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct ath79_spi *sp;
	struct ath79_spi_platform_data *pdata;
	struct resource	*r;
	unsigned long rate;
	int ret;

	master = spi_alloc_master(&pdev->dev, sizeof(*sp));
	if (master == NULL) {
		dev_err(&pdev->dev, "failed to allocate spi master\n");
		return -ENOMEM;
	}

	sp = spi_master_get_devdata(master);
	master->dev.of_node = pdev->dev.of_node;
	platform_set_drvdata(pdev, sp);

	pdata = dev_get_platdata(&pdev->dev);

	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);
	master->setup = ath79_spi_setup;
	master->cleanup = ath79_spi_cleanup;
	if (pdata) {
		master->bus_num = pdata->bus_num;
		master->num_chipselect = pdata->num_chipselect;
	}

	sp->bitbang.master = master;
	sp->bitbang.chipselect = ath79_spi_chipselect;
	sp->bitbang.txrx_word[SPI_MODE_0] = ath79_spi_txrx_mode0;
	sp->bitbang.setup_transfer = spi_bitbang_setup_transfer;
	sp->bitbang.flags = SPI_CS_HIGH;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sp->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(sp->base)) {
		ret = PTR_ERR(sp->base);
		goto err_put_master;
	}

	sp->clk = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(sp->clk)) {
		ret = PTR_ERR(sp->clk);
		goto err_put_master;
	}

	ret = clk_prepare_enable(sp->clk);
	if (ret)
		goto err_put_master;

	rate = DIV_ROUND_UP(clk_get_rate(sp->clk), MHZ);
	if (!rate) {
		ret = -EINVAL;
		goto err_clk_disable;
	}

	sp->rrw_delay = ATH79_SPI_RRW_DELAY_FACTOR / rate;
	dev_dbg(&pdev->dev, "register read/write delay is %u nsecs\n",
		sp->rrw_delay);

	ath79_spi_enable(sp);
	ret = spi_bitbang_start(&sp->bitbang);
	if (ret)
		goto err_disable;

	return 0;

err_disable:
	ath79_spi_disable(sp);
err_clk_disable:
	clk_disable_unprepare(sp->clk);
err_put_master:
	spi_master_put(sp->bitbang.master);

	return ret;
}