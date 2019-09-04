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
struct spi_transfer {int len; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  cs_gpio; } ;

/* Variables and functions */
 int BCM2835_SPI_DMA_MIN_LENGTH ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bcm2835_spi_can_dma(struct spi_master *master,
				struct spi_device *spi,
				struct spi_transfer *tfr)
{
	/* only run for gpio_cs */
	if (!gpio_is_valid(spi->cs_gpio))
		return false;

	/* we start DMA efforts only on bigger transfers */
	if (tfr->len < BCM2835_SPI_DMA_MIN_LENGTH)
		return false;

	/* BCM2835_SPI_DLEN has defined a max transfer size as
	 * 16 bit, so max is 65535
	 * we can revisit this by using an alternative transfer
	 * method - ideally this would get done without any more
	 * interaction...
	 */
	if (tfr->len > 65535) {
		dev_warn_once(&spi->dev,
			      "transfer size of %d too big for dma-transfer\n",
			      tfr->len);
		return false;
	}

	/* if we run rx/tx_buf with word aligned addresses then we are OK */
	if ((((size_t)tfr->rx_buf & 3) == 0) &&
	    (((size_t)tfr->tx_buf & 3) == 0))
		return true;

	/* otherwise we only allow transfers within the same page
	 * to avoid wasting time on dma_mapping when it is not practical
	 */
	if (((size_t)tfr->tx_buf & (PAGE_SIZE - 1)) + tfr->len > PAGE_SIZE) {
		dev_warn_once(&spi->dev,
			      "Unaligned spi tx-transfer bridging page\n");
		return false;
	}
	if (((size_t)tfr->rx_buf & (PAGE_SIZE - 1)) + tfr->len > PAGE_SIZE) {
		dev_warn_once(&spi->dev,
			      "Unaligned spi rx-transfer bridging page\n");
		return false;
	}

	/* return OK */
	return true;
}