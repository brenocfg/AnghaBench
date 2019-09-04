#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct spi_transfer {int bits_per_word; scalar_t__ rx_buf; } ;
struct spi_master {TYPE_1__* cur_msg; } ;
struct ep93xx_spi {size_t rx; scalar_t__ mmio; } ;
struct TYPE_2__ {struct spi_transfer* state; } ;

/* Variables and functions */
 scalar_t__ SSPDR ; 
 void* readl (scalar_t__) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void ep93xx_do_read(struct spi_master *master)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	struct spi_transfer *xfer = master->cur_msg->state;
	u32 val;

	val = readl(espi->mmio + SSPDR);
	if (xfer->bits_per_word > 8) {
		if (xfer->rx_buf)
			((u16 *)xfer->rx_buf)[espi->rx] = val;
		espi->rx += 2;
	} else {
		if (xfer->rx_buf)
			((u8 *)xfer->rx_buf)[espi->rx] = val;
		espi->rx += 1;
	}
}