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
typedef  int u32 ;
struct spi_device {struct pxa2xx_spi_chip* controller_data; } ;
struct pxa2xx_spi_chip {int dma_burst_size; } ;
struct chip_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_THRESH_DFLT ; 
 int SSCR1_RxTresh (int /*<<< orphan*/ ) ; 
 int SSCR1_TxTresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_THRESH_DFLT ; 

int pxa2xx_spi_set_dma_burst_and_threshold(struct chip_data *chip,
					   struct spi_device *spi,
					   u8 bits_per_word, u32 *burst_code,
					   u32 *threshold)
{
	struct pxa2xx_spi_chip *chip_info = spi->controller_data;

	/*
	 * If the DMA burst size is given in chip_info we use that,
	 * otherwise we use the default. Also we use the default FIFO
	 * thresholds for now.
	 */
	*burst_code = chip_info ? chip_info->dma_burst_size : 1;
	*threshold = SSCR1_RxTresh(RX_THRESH_DFLT)
		   | SSCR1_TxTresh(TX_THRESH_DFLT);

	return 0;
}