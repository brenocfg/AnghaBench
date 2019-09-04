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
struct spi_transfer {int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  len; } ;
struct spi_engine {int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  tx_length; struct spi_transfer* tx_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_engine_xfer_next (struct spi_engine*,struct spi_transfer**) ; 

__attribute__((used)) static void spi_engine_tx_next(struct spi_engine *spi_engine)
{
	struct spi_transfer *xfer = spi_engine->tx_xfer;

	do {
		spi_engine_xfer_next(spi_engine, &xfer);
	} while (xfer && !xfer->tx_buf);

	spi_engine->tx_xfer = xfer;
	if (xfer) {
		spi_engine->tx_length = xfer->len;
		spi_engine->tx_buf = xfer->tx_buf;
	} else {
		spi_engine->tx_buf = NULL;
	}
}