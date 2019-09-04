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
struct spi_transfer {scalar_t__ len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  rx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {struct davinci_spi_config* controller_data; } ;
struct davinci_spi_config {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ DMA_MIN_BYTES ; 
 scalar_t__ SPI_IO_TYPE_DMA ; 
 int /*<<< orphan*/  is_vmalloc_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool davinci_spi_can_dma(struct spi_master *master,
				struct spi_device *spi,
				struct spi_transfer *xfer)
{
	struct davinci_spi_config *spicfg = spi->controller_data;
	bool can_dma = false;

	if (spicfg)
		can_dma = (spicfg->io_type == SPI_IO_TYPE_DMA) &&
			(xfer->len >= DMA_MIN_BYTES) &&
			!is_vmalloc_addr(xfer->rx_buf) &&
			!is_vmalloc_addr(xfer->tx_buf);

	return can_dma;
}