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
struct tegra_uart_port {unsigned long lcr_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
 unsigned long UART_LCR_SBC ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_break_ctl(struct uart_port *u, int break_ctl)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	unsigned long lcr;

	lcr = tup->lcr_shadow;
	if (break_ctl)
		lcr |= UART_LCR_SBC;
	else
		lcr &= ~UART_LCR_SBC;
	tegra_uart_write(tup, lcr, UART_LCR);
	tup->lcr_shadow = lcr;
}