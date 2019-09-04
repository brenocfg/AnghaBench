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
typedef  int /*<<< orphan*/  const u16 ;
struct davinci_spi {int /*<<< orphan*/  const* tx; } ;

/* Variables and functions */

__attribute__((used)) static u32 davinci_spi_tx_buf_u16(struct davinci_spi *dspi)
{
	u32 data = 0;

	if (dspi->tx) {
		const u16 *tx = dspi->tx;

		data = *tx++;
		dspi->tx = tx;
	}
	return data;
}