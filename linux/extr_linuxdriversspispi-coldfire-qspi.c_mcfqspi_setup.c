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
struct spi_device {int mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int MCFQSPI_BUSCLK ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcfqspi_cs_deselect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mcfqspi_qmr_baud (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcfqspi_setup(struct spi_device *spi)
{
	mcfqspi_cs_deselect(spi_master_get_devdata(spi->master),
			    spi->chip_select, spi->mode & SPI_CS_HIGH);

	dev_dbg(&spi->dev,
			"bits per word %d, chip select %d, speed %d KHz\n",
			spi->bits_per_word, spi->chip_select,
			(MCFQSPI_BUSCLK / mcfqspi_qmr_baud(spi->max_speed_hz))
			/ 1000);

	return 0;
}