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
struct lantiq_ssc_spi {unsigned int tx_fifo_size; } ;

/* Variables and functions */
 unsigned int tx_fifo_level (struct lantiq_ssc_spi const*) ; 

__attribute__((used)) static unsigned int tx_fifo_free(const struct lantiq_ssc_spi *spi)
{
	return spi->tx_fifo_size - tx_fifo_level(spi);
}