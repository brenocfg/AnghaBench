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
struct uart_port {TYPE_1__* state; } ;
struct tegra_uart_port {int /*<<< orphan*/  tx_in_progress; } ;
struct circ_buf {int dummy; } ;
struct TYPE_2__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_uart_start_next_tx (struct tegra_uart_port*) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 

__attribute__((used)) static void tegra_uart_start_tx(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	struct circ_buf *xmit = &u->state->xmit;

	if (!uart_circ_empty(xmit) && !tup->tx_in_progress)
		tegra_uart_start_next_tx(tup);
}