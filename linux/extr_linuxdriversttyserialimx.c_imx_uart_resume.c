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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct imx_port {int /*<<< orphan*/  clk_ipg; TYPE_1__ port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct imx_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_enable_wakeup (struct imx_port*,int) ; 
 int /*<<< orphan*/  imx_uart_uart_driver ; 
 int /*<<< orphan*/  uart_resume_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int imx_uart_resume(struct device *dev)
{
	struct imx_port *sport = dev_get_drvdata(dev);

	/* disable wakeup from i.MX UART */
	imx_uart_enable_wakeup(sport, false);

	uart_resume_port(&imx_uart_uart_driver, &sport->port);
	enable_irq(sport->port.irq);

	clk_disable_unprepare(sport->clk_ipg);

	return 0;
}