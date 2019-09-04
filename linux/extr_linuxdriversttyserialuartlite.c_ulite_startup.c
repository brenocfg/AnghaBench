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
struct uartlite_data {int /*<<< orphan*/  clk; } ;
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; struct uartlite_data* private_data; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  ULITE_CONTROL ; 
 int ULITE_CONTROL_IE ; 
 int ULITE_CONTROL_RST_RX ; 
 int ULITE_CONTROL_RST_TX ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct uart_port*) ; 
 int /*<<< orphan*/  uart_out32 (int,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  ulite_isr ; 

__attribute__((used)) static int ulite_startup(struct uart_port *port)
{
	struct uartlite_data *pdata = port->private_data;
	int ret;

	ret = clk_enable(pdata->clk);
	if (ret) {
		dev_err(port->dev, "Failed to enable clock\n");
		return ret;
	}

	ret = request_irq(port->irq, ulite_isr, IRQF_SHARED | IRQF_TRIGGER_RISING,
			  "uartlite", port);
	if (ret)
		return ret;

	uart_out32(ULITE_CONTROL_RST_RX | ULITE_CONTROL_RST_TX,
		ULITE_CONTROL, port);
	uart_out32(ULITE_CONTROL_IE, ULITE_CONTROL, port);

	return 0;
}