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
struct uart_8250_port {unsigned char ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 unsigned char UART_IER_RDI ; 
 unsigned char UART_IER_RLSI ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void __aspeed_vuart_set_throttle(struct uart_8250_port *up,
		bool throttle)
{
	unsigned char irqs = UART_IER_RLSI | UART_IER_RDI;

	up->ier &= ~irqs;
	if (!throttle)
		up->ier |= irqs;
	serial_out(up, UART_IER, up->ier);
}