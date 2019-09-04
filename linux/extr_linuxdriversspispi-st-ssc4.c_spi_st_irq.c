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
struct spi_st {int /*<<< orphan*/  done; scalar_t__ base; scalar_t__ words_remaining; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SSC_IEN ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  ssc_read_rx_fifo (struct spi_st*) ; 
 int /*<<< orphan*/  ssc_write_tx_fifo (struct spi_st*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t spi_st_irq(int irq, void *dev_id)
{
	struct spi_st *spi_st = (struct spi_st *)dev_id;

	/* Read RX FIFO */
	ssc_read_rx_fifo(spi_st);

	/* Fill TX FIFO */
	if (spi_st->words_remaining) {
		ssc_write_tx_fifo(spi_st);
	} else {
		/* TX/RX complete */
		writel_relaxed(0x0, spi_st->base + SSC_IEN);
		/*
		 * read SSC_IEN to ensure that this bit is set
		 * before re-enabling interrupt
		 */
		readl(spi_st->base + SSC_IEN);
		complete(&spi_st->done);
	}

	return IRQ_HANDLED;
}