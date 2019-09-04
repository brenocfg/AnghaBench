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
typedef  unsigned int u32 ;
struct spi_transfer {scalar_t__ speed_hz; scalar_t__ bits_per_word; } ;
struct spi_device {unsigned int bits_per_word; unsigned int max_speed_hz; int mode; int /*<<< orphan*/  master; } ;
struct efm32_spi_ddata {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_CLKDIV ; 
 int /*<<< orphan*/  REG_CMD ; 
 unsigned int REG_CMD_MASTEREN ; 
 unsigned int REG_CMD_RXEN ; 
 unsigned int REG_CMD_TXEN ; 
 int /*<<< orphan*/  REG_CTRL ; 
 unsigned int REG_CTRL_CLKPHA ; 
 unsigned int REG_CTRL_CLKPOL ; 
 unsigned int REG_CTRL_MSBF ; 
 unsigned int REG_CTRL_SYNC ; 
 int /*<<< orphan*/  REG_FRAME ; 
 unsigned int REG_FRAME_DATABITS (unsigned int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_spi_write32 (struct efm32_spi_ddata*,unsigned int,int /*<<< orphan*/ ) ; 
 struct efm32_spi_ddata* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efm32_spi_setup_transfer(struct spi_device *spi,
		struct spi_transfer *t)
{
	struct efm32_spi_ddata *ddata = spi_master_get_devdata(spi->master);

	unsigned bpw = t->bits_per_word ?: spi->bits_per_word;
	unsigned speed = t->speed_hz ?: spi->max_speed_hz;
	unsigned long clkfreq = clk_get_rate(ddata->clk);
	u32 clkdiv;

	efm32_spi_write32(ddata, REG_CTRL_SYNC | REG_CTRL_MSBF |
			(spi->mode & SPI_CPHA ? REG_CTRL_CLKPHA : 0) |
			(spi->mode & SPI_CPOL ? REG_CTRL_CLKPOL : 0), REG_CTRL);

	efm32_spi_write32(ddata,
			REG_FRAME_DATABITS(bpw), REG_FRAME);

	if (2 * speed >= clkfreq)
		clkdiv = 0;
	else
		clkdiv = 64 * (DIV_ROUND_UP(2 * clkfreq, speed) - 4);

	if (clkdiv > (1U << 21))
		return -EINVAL;

	efm32_spi_write32(ddata, clkdiv, REG_CLKDIV);
	efm32_spi_write32(ddata, REG_CMD_MASTEREN, REG_CMD);
	efm32_spi_write32(ddata, REG_CMD_RXEN | REG_CMD_TXEN, REG_CMD);

	return 0;
}