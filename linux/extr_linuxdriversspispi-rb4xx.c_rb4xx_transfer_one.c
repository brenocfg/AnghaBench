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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int len; scalar_t__ tx_nbits; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int chip_select; } ;
struct rb4xx_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_SPI_IOC_CS0 ; 
 int /*<<< orphan*/  AR71XX_SPI_IOC_CS1 ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_RDS ; 
 scalar_t__ SPI_NBITS_DUAL ; 
 int /*<<< orphan*/  do_spi_byte (struct rb4xx_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  do_spi_byte_two (struct rb4xx_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rb4xx_read (struct rb4xx_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct rb4xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int rb4xx_transfer_one(struct spi_master *master,
			      struct spi_device *spi, struct spi_transfer *t)
{
	struct rb4xx_spi *rbspi = spi_master_get_devdata(master);
	int i;
	u32 spi_ioc;
	u8 *rx_buf;
	const u8 *tx_buf;

	/*
	 * Prime the SPI register with the SPI device selected. The m25p80 boot
	 * flash and CPLD share the CS0 pin. This works because the CPLD's
	 * command set was designed to almost not clash with that of the
	 * boot flash.
	 */
	if (spi->chip_select == 2)
		/* MMC */
		spi_ioc = AR71XX_SPI_IOC_CS0;
	else
		/* Boot flash and CPLD */
		spi_ioc = AR71XX_SPI_IOC_CS1;

	tx_buf = t->tx_buf;
	rx_buf = t->rx_buf;
	for (i = 0; i < t->len; ++i) {
		if (t->tx_nbits == SPI_NBITS_DUAL)
			/* CPLD can use two-wire transfers */
			do_spi_byte_two(rbspi, spi_ioc, tx_buf[i]);
		else
			do_spi_byte(rbspi, spi_ioc, tx_buf[i]);
		if (!rx_buf)
			continue;
		rx_buf[i] = rb4xx_read(rbspi, AR71XX_SPI_REG_RDS);
	}
	spi_finalize_current_transfer(master);

	return 0;
}