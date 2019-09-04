#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_message {TYPE_1__* spi; } ;
struct spi_master {int dummy; } ;
struct rspi_data {int dummy; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPI_SPCR ; 
 int SPCR_SPE ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int qspi_setup_sequencer (struct rspi_data*,struct spi_message*) ; 
 int rspi_read8 (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 
 struct rspi_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int rspi_prepare_message(struct spi_master *master,
				struct spi_message *msg)
{
	struct rspi_data *rspi = spi_master_get_devdata(master);
	int ret;

	if (msg->spi->mode &
	    (SPI_TX_DUAL | SPI_TX_QUAD | SPI_RX_DUAL | SPI_RX_QUAD)) {
		/* Setup sequencer for messages with multiple transfer modes */
		ret = qspi_setup_sequencer(rspi, msg);
		if (ret < 0)
			return ret;
	}

	/* Enable SPI function in master mode */
	rspi_write8(rspi, rspi_read8(rspi, RSPI_SPCR) | SPCR_SPE, RSPI_SPCR);
	return 0;
}