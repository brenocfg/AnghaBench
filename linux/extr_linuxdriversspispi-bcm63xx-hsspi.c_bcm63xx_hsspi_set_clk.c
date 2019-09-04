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
struct spi_device {unsigned int chip_select; int mode; } ;
struct bcm63xx_hsspi {int speed_hz; int /*<<< orphan*/  bus_mutex; scalar_t__ regs; } ;

/* Variables and functions */
 int CLK_CTRL_ACCUM_RST_ON_LOOP ; 
 int DIV_ROUND_UP (int,int) ; 
 int GLOBAL_CTRL_CLK_POLARITY ; 
 scalar_t__ HSSPI_GLOBAL_CTRL_REG ; 
 int HSSPI_MAX_SYNC_CLOCK ; 
 scalar_t__ HSSPI_PROFILE_CLK_CTRL_REG (unsigned int) ; 
 scalar_t__ HSSPI_PROFILE_SIGNAL_CTRL_REG (unsigned int) ; 
 int SIGNAL_CTRL_ASYNC_INPUT_PATH ; 
 int SPI_CPOL ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm63xx_hsspi_set_clk(struct bcm63xx_hsspi *bs,
				  struct spi_device *spi, int hz)
{
	unsigned int profile = spi->chip_select;
	u32 reg;

	reg = DIV_ROUND_UP(2048, DIV_ROUND_UP(bs->speed_hz, hz));
	__raw_writel(CLK_CTRL_ACCUM_RST_ON_LOOP | reg,
		     bs->regs + HSSPI_PROFILE_CLK_CTRL_REG(profile));

	reg = __raw_readl(bs->regs + HSSPI_PROFILE_SIGNAL_CTRL_REG(profile));
	if (hz > HSSPI_MAX_SYNC_CLOCK)
		reg |= SIGNAL_CTRL_ASYNC_INPUT_PATH;
	else
		reg &= ~SIGNAL_CTRL_ASYNC_INPUT_PATH;
	__raw_writel(reg, bs->regs + HSSPI_PROFILE_SIGNAL_CTRL_REG(profile));

	mutex_lock(&bs->bus_mutex);
	/* setup clock polarity */
	reg = __raw_readl(bs->regs + HSSPI_GLOBAL_CTRL_REG);
	reg &= ~GLOBAL_CTRL_CLK_POLARITY;
	if (spi->mode & SPI_CPOL)
		reg |= GLOBAL_CTRL_CLK_POLARITY;
	__raw_writel(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	mutex_unlock(&bs->bus_mutex);
}