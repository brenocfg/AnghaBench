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
struct rockchip_spi {int tx; int tx_end; int rx; int rx_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  rockchip_spi_pio_reader (struct rockchip_spi*) ; 
 int /*<<< orphan*/  rockchip_spi_pio_writer (struct rockchip_spi*) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_idle (struct rockchip_spi*) ; 

__attribute__((used)) static int rockchip_spi_pio_transfer(struct rockchip_spi *rs)
{
	int remain = 0;

	do {
		if (rs->tx) {
			remain = rs->tx_end - rs->tx;
			rockchip_spi_pio_writer(rs);
		}

		if (rs->rx) {
			remain = rs->rx_end - rs->rx;
			rockchip_spi_pio_reader(rs);
		}

		cpu_relax();
	} while (remain);

	/* If tx, wait until the FIFO data completely. */
	if (rs->tx)
		wait_for_idle(rs);

	spi_enable_chip(rs, 0);

	return 0;
}