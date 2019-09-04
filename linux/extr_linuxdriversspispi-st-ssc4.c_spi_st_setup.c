#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct spi_st {int baud; scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct spi_device {int max_speed_hz; int cs_gpio; int mode; int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 scalar_t__ SSC_BRG ; 
 scalar_t__ SSC_CTL ; 
 int SSC_CTL_DATA_WIDTH_MSK ; 
 int SSC_CTL_EN ; 
 int SSC_CTL_EN_RX_FIFO ; 
 int SSC_CTL_EN_TX_FIFO ; 
 int SSC_CTL_HB ; 
 int SSC_CTL_LPB ; 
 int SSC_CTL_MS ; 
 int SSC_CTL_PH ; 
 int SSC_CTL_PO ; 
 scalar_t__ SSC_RBUF ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 struct spi_st* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spi_st_setup(struct spi_device *spi)
{
	struct spi_st *spi_st = spi_master_get_devdata(spi->master);
	u32 spi_st_clk, sscbrg, var;
	u32 hz = spi->max_speed_hz;
	int cs = spi->cs_gpio;
	int ret;

	if (!hz)  {
		dev_err(&spi->dev, "max_speed_hz unspecified\n");
		return -EINVAL;
	}

	if (!gpio_is_valid(cs)) {
		dev_err(&spi->dev, "%d is not a valid gpio\n", cs);
		return -EINVAL;
	}

	ret = gpio_request(cs, dev_name(&spi->dev));
	if (ret) {
		dev_err(&spi->dev, "could not request gpio:%d\n", cs);
		return ret;
	}

	ret = gpio_direction_output(cs, spi->mode & SPI_CS_HIGH);
	if (ret)
		goto out_free_gpio;

	spi_st_clk = clk_get_rate(spi_st->clk);

	/* Set SSC_BRF */
	sscbrg = spi_st_clk / (2 * hz);
	if (sscbrg < 0x07 || sscbrg > BIT(16)) {
		dev_err(&spi->dev,
			"baudrate %d outside valid range %d\n", sscbrg, hz);
		ret = -EINVAL;
		goto out_free_gpio;
	}

	spi_st->baud = spi_st_clk / (2 * sscbrg);
	if (sscbrg == BIT(16)) /* 16-bit counter wraps */
		sscbrg = 0x0;

	writel_relaxed(sscbrg, spi_st->base + SSC_BRG);

	dev_dbg(&spi->dev,
		"setting baudrate:target= %u hz, actual= %u hz, sscbrg= %u\n",
		hz, spi_st->baud, sscbrg);

	/* Set SSC_CTL and enable SSC */
	var = readl_relaxed(spi_st->base + SSC_CTL);
	var |= SSC_CTL_MS;

	if (spi->mode & SPI_CPOL)
		var |= SSC_CTL_PO;
	else
		var &= ~SSC_CTL_PO;

	if (spi->mode & SPI_CPHA)
		var |= SSC_CTL_PH;
	else
		var &= ~SSC_CTL_PH;

	if ((spi->mode & SPI_LSB_FIRST) == 0)
		var |= SSC_CTL_HB;
	else
		var &= ~SSC_CTL_HB;

	if (spi->mode & SPI_LOOP)
		var |= SSC_CTL_LPB;
	else
		var &= ~SSC_CTL_LPB;

	var &= ~SSC_CTL_DATA_WIDTH_MSK;
	var |= (spi->bits_per_word - 1);

	var |= SSC_CTL_EN_TX_FIFO | SSC_CTL_EN_RX_FIFO;
	var |= SSC_CTL_EN;

	writel_relaxed(var, spi_st->base + SSC_CTL);

	/* Clear the status register */
	readl_relaxed(spi_st->base + SSC_RBUF);

	return 0;

out_free_gpio:
	gpio_free(cs);
	return ret;
}