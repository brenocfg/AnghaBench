#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* state; } ;
struct tegra_uart_port {TYPE_2__ uport; scalar_t__ tx_in_progress; int /*<<< orphan*/  tx_bytes; } ;
struct circ_buf {int dummy; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  tegra_uart_fill_tx_fifo (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_start_next_tx (struct tegra_uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_2__*) ; 

__attribute__((used)) static void tegra_uart_handle_tx_pio(struct tegra_uart_port *tup)
{
	struct circ_buf *xmit = &tup->uport.state->xmit;

	tegra_uart_fill_tx_fifo(tup, tup->tx_bytes);
	tup->tx_in_progress = 0;
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&tup->uport);
	tegra_uart_start_next_tx(tup);
}