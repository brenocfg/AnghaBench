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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct uart_omap_port {int /*<<< orphan*/  dev; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_EFR ; 
 unsigned char UART_EFR_ECB ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned char UART_IERX_SLEEP ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_CONF_MODE_B ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 unsigned char serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,unsigned char) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void
serial_omap_pm(struct uart_port *port, unsigned int state,
	       unsigned int oldstate)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned char efr;

	dev_dbg(up->port.dev, "serial_omap_pm+%d\n", up->port.line);

	pm_runtime_get_sync(up->dev);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	efr = serial_in(up, UART_EFR);
	serial_out(up, UART_EFR, efr | UART_EFR_ECB);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_IER, (state != 0) ? UART_IERX_SLEEP : 0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, efr);
	serial_out(up, UART_LCR, 0);

	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
}