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
struct spi_master {int dummy; } ;
struct cdns_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_SPI_ER ; 
 int /*<<< orphan*/  CDNS_SPI_ER_ENABLE ; 
 int /*<<< orphan*/  cdns_spi_write (struct cdns_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdns_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int cdns_prepare_transfer_hardware(struct spi_master *master)
{
	struct cdns_spi *xspi = spi_master_get_devdata(master);

	cdns_spi_write(xspi, CDNS_SPI_ER, CDNS_SPI_ER_ENABLE);

	return 0;
}