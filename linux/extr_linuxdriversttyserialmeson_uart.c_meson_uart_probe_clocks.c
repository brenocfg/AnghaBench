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
struct uart_port {int /*<<< orphan*/  uartclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 struct clk* meson_uart_probe_clock (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int meson_uart_probe_clocks(struct platform_device *pdev,
				   struct uart_port *port)
{
	struct clk *clk_xtal = NULL;
	struct clk *clk_pclk = NULL;
	struct clk *clk_baud = NULL;

	clk_pclk = meson_uart_probe_clock(&pdev->dev, "pclk");
	if (IS_ERR(clk_pclk))
		return PTR_ERR(clk_pclk);

	clk_xtal = meson_uart_probe_clock(&pdev->dev, "xtal");
	if (IS_ERR(clk_xtal))
		return PTR_ERR(clk_xtal);

	clk_baud = meson_uart_probe_clock(&pdev->dev, "baud");
	if (IS_ERR(clk_baud))
		return PTR_ERR(clk_baud);

	port->uartclk = clk_get_rate(clk_baud);

	return 0;
}