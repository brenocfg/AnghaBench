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
struct lantiq_ssc_spi {unsigned int rx_todo; int rx_fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_RXREQ ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_request(struct lantiq_ssc_spi *spi)
{
	unsigned int rxreq, rxreq_max;

	/*
	 * To avoid receive overflows at high clocks it is better to request
	 * only the amount of bytes that fits into all FIFOs. This value
	 * depends on the FIFO size implemented in hardware.
	 */
	rxreq = spi->rx_todo;
	rxreq_max = spi->rx_fifo_size * 4;
	if (rxreq > rxreq_max)
		rxreq = rxreq_max;

	lantiq_ssc_writel(spi, rxreq, LTQ_SPI_RXREQ);
}