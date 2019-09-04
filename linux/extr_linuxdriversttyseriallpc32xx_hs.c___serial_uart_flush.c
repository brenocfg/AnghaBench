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
typedef  scalar_t__ u32 ;
struct uart_port {int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_READ_LIMIT ; 
 int /*<<< orphan*/  LPC32XX_HSUART_FIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSUART_LEVEL (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __serial_uart_flush(struct uart_port *port)
{
	u32 tmp;
	int cnt = 0;

	while ((readl(LPC32XX_HSUART_LEVEL(port->membase)) > 0) &&
	       (cnt++ < FIFO_READ_LIMIT))
		tmp = readl(LPC32XX_HSUART_FIFO(port->membase));
}