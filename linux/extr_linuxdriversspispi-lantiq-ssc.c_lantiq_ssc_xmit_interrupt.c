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
struct lantiq_ssc_spi {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; scalar_t__ rx_todo; scalar_t__ rx; scalar_t__ tx_todo; scalar_t__ tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_fifo_read_full_duplex (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  rx_fifo_read_half_duplex (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  rx_request (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  tx_fifo_level (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  tx_fifo_write (struct lantiq_ssc_spi*) ; 

__attribute__((used)) static irqreturn_t lantiq_ssc_xmit_interrupt(int irq, void *data)
{
	struct lantiq_ssc_spi *spi = data;

	if (spi->tx) {
		if (spi->rx && spi->rx_todo)
			rx_fifo_read_full_duplex(spi);

		if (spi->tx_todo)
			tx_fifo_write(spi);
		else if (!tx_fifo_level(spi))
			goto completed;
	} else if (spi->rx) {
		if (spi->rx_todo) {
			rx_fifo_read_half_duplex(spi);

			if (spi->rx_todo)
				rx_request(spi);
			else
				goto completed;
		} else {
			goto completed;
		}
	}

	return IRQ_HANDLED;

completed:
	queue_work(spi->wq, &spi->work);

	return IRQ_HANDLED;
}