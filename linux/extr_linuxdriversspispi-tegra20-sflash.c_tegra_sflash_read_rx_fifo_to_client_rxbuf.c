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
struct tegra_sflash_data {int cur_rx_pos; int bytes_per_word; } ;
struct spi_transfer {scalar_t__ rx_buf; } ;

/* Variables and functions */
 int SPI_RXF_EMPTY ; 
 int /*<<< orphan*/  SPI_RX_FIFO ; 
 int /*<<< orphan*/  SPI_STATUS ; 
 int tegra_sflash_readl (struct tegra_sflash_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_sflash_read_rx_fifo_to_client_rxbuf(
		struct tegra_sflash_data *tsd, struct spi_transfer *t)
{
	u32 status;
	unsigned int read_words = 0;
	u8 *rx_buf = (u8 *)t->rx_buf + tsd->cur_rx_pos;

	status = tegra_sflash_readl(tsd, SPI_STATUS);
	while (!(status & SPI_RXF_EMPTY)) {
		int i;
		u32 x = tegra_sflash_readl(tsd, SPI_RX_FIFO);

		for (i = 0; (i < tsd->bytes_per_word); i++)
			*rx_buf++ = (x >> (i*8)) & 0xFF;
		read_words++;
		status = tegra_sflash_readl(tsd, SPI_STATUS);
	}
	tsd->cur_rx_pos += read_words * tsd->bytes_per_word;
	return 0;
}