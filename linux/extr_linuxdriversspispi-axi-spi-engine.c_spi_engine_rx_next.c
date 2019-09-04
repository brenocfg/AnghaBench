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
struct spi_transfer {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  len; } ;
struct spi_engine {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  rx_length; struct spi_transfer* rx_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_engine_xfer_next (struct spi_engine*,struct spi_transfer**) ; 

__attribute__((used)) static void spi_engine_rx_next(struct spi_engine *spi_engine)
{
	struct spi_transfer *xfer = spi_engine->rx_xfer;

	do {
		spi_engine_xfer_next(spi_engine, &xfer);
	} while (xfer && !xfer->rx_buf);

	spi_engine->rx_xfer = xfer;
	if (xfer) {
		spi_engine->rx_length = xfer->len;
		spi_engine->rx_buf = xfer->rx_buf;
	} else {
		spi_engine->rx_buf = NULL;
	}
}