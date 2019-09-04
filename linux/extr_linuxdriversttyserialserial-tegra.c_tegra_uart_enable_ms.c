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
struct uart_port {int dummy; } ;
struct tegra_uart_port {int /*<<< orphan*/  ier_shadow; scalar_t__ enable_modem_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_enable_ms(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);

	if (tup->enable_modem_interrupt) {
		tup->ier_shadow |= UART_IER_MSI;
		tegra_uart_write(tup, tup->ier_shadow, UART_IER);
	}
}