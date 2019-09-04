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
struct tegra_sflash_data {unsigned int cur_pos; unsigned int bytes_per_word; unsigned int curr_xfer_words; } ;
struct spi_transfer {unsigned int len; int /*<<< orphan*/  bits_per_word; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 unsigned int SPI_FIFO_DEPTH ; 

__attribute__((used)) static unsigned tegra_sflash_calculate_curr_xfer_param(
	struct spi_device *spi, struct tegra_sflash_data *tsd,
	struct spi_transfer *t)
{
	unsigned remain_len = t->len - tsd->cur_pos;
	unsigned max_word;

	tsd->bytes_per_word = DIV_ROUND_UP(t->bits_per_word, 8);
	max_word = remain_len / tsd->bytes_per_word;
	if (max_word > SPI_FIFO_DEPTH)
		max_word = SPI_FIFO_DEPTH;
	tsd->curr_xfer_words = max_word;
	return max_word;
}