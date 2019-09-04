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
struct platform_device {int dummy; } ;
struct lpc18xx_uart_data {int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk_uart; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpc18xx_uart_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_serial_remove(struct platform_device *pdev)
{
	struct lpc18xx_uart_data *data = platform_get_drvdata(pdev);

	serial8250_unregister_port(data->line);
	clk_disable_unprepare(data->clk_uart);
	clk_disable_unprepare(data->clk_reg);

	return 0;
}