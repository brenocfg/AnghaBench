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
struct gb_spilib {scalar_t__ op_timeout; scalar_t__ last_xfer_size; scalar_t__ tx_xfer_offset; scalar_t__ rx_xfer_offset; int /*<<< orphan*/ * last_xfer; int /*<<< orphan*/ * first_xfer; } ;

/* Variables and functions */

__attribute__((used)) static void clean_xfer_state(struct gb_spilib *spi)
{
	spi->first_xfer = NULL;
	spi->last_xfer = NULL;
	spi->rx_xfer_offset = 0;
	spi->tx_xfer_offset = 0;
	spi->last_xfer_size = 0;
	spi->op_timeout = 0;
}