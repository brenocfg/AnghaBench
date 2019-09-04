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
struct tegra_uart_port {unsigned int tx_bytes; int /*<<< orphan*/  ier_shadow; int /*<<< orphan*/  tx_in_progress; } ;

/* Variables and functions */
 unsigned int TEGRA_UART_MIN_DMA ; 
 int /*<<< orphan*/  TEGRA_UART_TX_PIO ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_THRI ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_uart_start_pio_tx(struct tegra_uart_port *tup,
		unsigned int bytes)
{
	if (bytes > TEGRA_UART_MIN_DMA)
		bytes = TEGRA_UART_MIN_DMA;

	tup->tx_in_progress = TEGRA_UART_TX_PIO;
	tup->tx_bytes = bytes;
	tup->ier_shadow |= UART_IER_THRI;
	tegra_uart_write(tup, tup->ier_shadow, UART_IER);
}