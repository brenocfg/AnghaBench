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
struct spi_master {int num_chipselect; int /*<<< orphan*/  mode_bits; } ;
struct a3700_spi {struct spi_master* master; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_DIN_CNT_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_HDR_CNT_REG ; 
 int /*<<< orphan*/  A3700_SPI_INT_MASK_REG ; 
 int /*<<< orphan*/  A3700_SPI_INT_STAT_REG ; 
 unsigned int A3700_SPI_SRST ; 
 int /*<<< orphan*/  A3700_SPI_TIMEOUT ; 
 int /*<<< orphan*/  a3700_spi_auto_cs_unset (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_deactivate_cs (struct a3700_spi*,int) ; 
 int /*<<< orphan*/  a3700_spi_fifo_mode_set (struct a3700_spi*,int) ; 
 int /*<<< orphan*/  a3700_spi_mode_set (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 unsigned int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a3700_spi_init(struct a3700_spi *a3700_spi)
{
	struct spi_master *master = a3700_spi->master;
	u32 val;
	int i, ret = 0;

	/* Reset SPI unit */
	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	val |= A3700_SPI_SRST;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	udelay(A3700_SPI_TIMEOUT);

	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~A3700_SPI_SRST;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	/* Disable AUTO_CS and deactivate all chip-selects */
	a3700_spi_auto_cs_unset(a3700_spi);
	for (i = 0; i < master->num_chipselect; i++)
		a3700_spi_deactivate_cs(a3700_spi, i);

	/* Enable FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, true);

	/* Set SPI mode */
	a3700_spi_mode_set(a3700_spi, master->mode_bits);

	/* Reset counters */
	spireg_write(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_IF_DIN_CNT_REG, 0);

	/* Mask the interrupts and clear cause bits */
	spireg_write(a3700_spi, A3700_SPI_INT_MASK_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_INT_STAT_REG, ~0U);

	return ret;
}