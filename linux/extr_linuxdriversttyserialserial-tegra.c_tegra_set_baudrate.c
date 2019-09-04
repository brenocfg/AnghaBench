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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {unsigned int current_baud; unsigned long lcr_shadow; int /*<<< orphan*/  uart_clk; TYPE_2__ uport; TYPE_1__* cdata; } ;
struct TYPE_3__ {scalar_t__ support_clk_src_div; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned long UART_LCR_DLAB ; 
 int /*<<< orphan*/  UART_SCR ; 
 int /*<<< orphan*/  UART_TX ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_wait_sym_time (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_set_baudrate(struct tegra_uart_port *tup, unsigned int baud)
{
	unsigned long rate;
	unsigned int divisor;
	unsigned long lcr;
	int ret;

	if (tup->current_baud == baud)
		return 0;

	if (tup->cdata->support_clk_src_div) {
		rate = baud * 16;
		ret = clk_set_rate(tup->uart_clk, rate);
		if (ret < 0) {
			dev_err(tup->uport.dev,
				"clk_set_rate() failed for rate %lu\n", rate);
			return ret;
		}
		divisor = 1;
	} else {
		rate = clk_get_rate(tup->uart_clk);
		divisor = DIV_ROUND_CLOSEST(rate, baud * 16);
	}

	lcr = tup->lcr_shadow;
	lcr |= UART_LCR_DLAB;
	tegra_uart_write(tup, lcr, UART_LCR);

	tegra_uart_write(tup, divisor & 0xFF, UART_TX);
	tegra_uart_write(tup, ((divisor >> 8) & 0xFF), UART_IER);

	lcr &= ~UART_LCR_DLAB;
	tegra_uart_write(tup, lcr, UART_LCR);

	/* Dummy read to ensure the write is posted */
	tegra_uart_read(tup, UART_SCR);

	tup->current_baud = baud;

	/* wait two character intervals at new rate */
	tegra_uart_wait_sym_time(tup, 2);
	return 0;
}