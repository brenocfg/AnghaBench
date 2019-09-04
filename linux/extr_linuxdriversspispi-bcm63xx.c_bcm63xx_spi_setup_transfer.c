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
typedef  int u8 ;
struct spi_transfer {scalar_t__ speed_hz; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct bcm63xx_spi {int dummy; } ;

/* Variables and functions */
 int SPI_CLK_0_391MHZ ; 
 int /*<<< orphan*/  SPI_CLK_CFG ; 
 int SPI_CLK_MASK ; 
 scalar_t__** bcm63xx_spi_freq_table ; 
 int bcm_spi_readb (struct bcm63xx_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_spi_writeb (struct bcm63xx_spi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 struct bcm63xx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_spi_setup_transfer(struct spi_device *spi,
				      struct spi_transfer *t)
{
	struct bcm63xx_spi *bs = spi_master_get_devdata(spi->master);
	u8 clk_cfg, reg;
	int i;

	/* Default to lowest clock configuration */
	clk_cfg = SPI_CLK_0_391MHZ;

	/* Find the closest clock configuration */
	for (i = 0; i < SPI_CLK_MASK; i++) {
		if (t->speed_hz >= bcm63xx_spi_freq_table[i][0]) {
			clk_cfg = bcm63xx_spi_freq_table[i][1];
			break;
		}
	}

	/* clear existing clock configuration bits of the register */
	reg = bcm_spi_readb(bs, SPI_CLK_CFG);
	reg &= ~SPI_CLK_MASK;
	reg |= clk_cfg;

	bcm_spi_writeb(bs, reg, SPI_CLK_CFG);
	dev_dbg(&spi->dev, "Setting clock register to %02x (hz %d)\n",
		clk_cfg, t->speed_hz);
}