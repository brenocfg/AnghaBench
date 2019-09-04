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
struct uart_8250_port {struct uart_port port; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int npcm_get_divisor(struct uart_8250_port *up,
		unsigned int baud)
{
	struct uart_port *port = &up->port;

	return DIV_ROUND_CLOSEST(port->uartclk, 16 * baud + 2) - 2;
}