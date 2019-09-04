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
struct imx_port {int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct imx_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  imx_uart_uart_driver ; 
 int /*<<< orphan*/  uart_resume_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_uart_thaw(struct device *dev)
{
	struct imx_port *sport = dev_get_drvdata(dev);

	uart_resume_port(&imx_uart_uart_driver, &sport->port);

	clk_disable_unprepare(sport->clk_ipg);

	return 0;
}