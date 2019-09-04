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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct atmel_uart_port {int backup_imr; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_IDR ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int /*<<< orphan*/  ATMEL_US_IMR ; 
 int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_serial_pm(struct uart_port *port, unsigned int state,
			    unsigned int oldstate)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	switch (state) {
	case 0:
		/*
		 * Enable the peripheral clock for this serial port.
		 * This is called on uart_open() or a resume event.
		 */
		clk_prepare_enable(atmel_port->clk);

		/* re-enable interrupts if we disabled some on suspend */
		atmel_uart_writel(port, ATMEL_US_IER, atmel_port->backup_imr);
		break;
	case 3:
		/* Back up the interrupt mask and disable all interrupts */
		atmel_port->backup_imr = atmel_uart_readl(port, ATMEL_US_IMR);
		atmel_uart_writel(port, ATMEL_US_IDR, -1);

		/*
		 * Disable the peripheral clock for this serial port.
		 * This is called on uart_close() or a suspend event.
		 */
		clk_disable_unprepare(atmel_port->clk);
		break;
	default:
		dev_err(port->dev, "atmel_serial: unknown pm %d\n", state);
	}
}