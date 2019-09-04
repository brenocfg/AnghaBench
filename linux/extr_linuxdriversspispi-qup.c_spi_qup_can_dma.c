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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int len; int /*<<< orphan*/  bits_per_word; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_qup {int in_blk_sz; int out_blk_sz; int in_fifo_sz; scalar_t__ qup_v1; } ;
struct spi_master {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (size_t,size_t) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 size_t dma_get_cache_alignment () ; 
 struct spi_qup* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static bool spi_qup_can_dma(struct spi_master *master, struct spi_device *spi,
			    struct spi_transfer *xfer)
{
	struct spi_qup *qup = spi_master_get_devdata(master);
	size_t dma_align = dma_get_cache_alignment();
	int n_words;

	if (xfer->rx_buf) {
		if (!IS_ALIGNED((size_t)xfer->rx_buf, dma_align) ||
		    IS_ERR_OR_NULL(master->dma_rx))
			return false;
		if (qup->qup_v1 && (xfer->len % qup->in_blk_sz))
			return false;
	}

	if (xfer->tx_buf) {
		if (!IS_ALIGNED((size_t)xfer->tx_buf, dma_align) ||
		    IS_ERR_OR_NULL(master->dma_tx))
			return false;
		if (qup->qup_v1 && (xfer->len % qup->out_blk_sz))
			return false;
	}

	n_words = xfer->len / DIV_ROUND_UP(xfer->bits_per_word, 8);
	if (n_words <= (qup->in_fifo_sz / sizeof(u32)))
		return false;

	return true;
}