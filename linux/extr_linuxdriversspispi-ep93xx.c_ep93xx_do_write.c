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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct spi_transfer {int bits_per_word; scalar_t__ tx_buf; } ;
struct spi_master {TYPE_1__* cur_msg; } ;
struct ep93xx_spi {size_t tx; scalar_t__ mmio; } ;
struct TYPE_2__ {struct spi_transfer* state; } ;

/* Variables and functions */
 scalar_t__ SSPDR ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ep93xx_do_write(struct spi_master *master)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	struct spi_transfer *xfer = master->cur_msg->state;
	u32 val = 0;

	if (xfer->bits_per_word > 8) {
		if (xfer->tx_buf)
			val = ((u16 *)xfer->tx_buf)[espi->tx];
		espi->tx += 2;
	} else {
		if (xfer->tx_buf)
			val = ((u8 *)xfer->tx_buf)[espi->tx];
		espi->tx += 1;
	}
	writel(val, espi->mmio + SSPDR);
}