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
struct uart_8250_port {int acr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_ACR ; 
 int UART_ACR_ICRRD ; 
 int /*<<< orphan*/  UART_ICR ; 
 int /*<<< orphan*/  UART_SCR ; 
 int /*<<< orphan*/  serial_icr_write (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int serial_icr_read(struct uart_8250_port *up, int offset)
{
	unsigned int value;

	serial_icr_write(up, UART_ACR, up->acr | UART_ACR_ICRRD);
	serial_out(up, UART_SCR, offset);
	value = serial_in(up, UART_ICR);
	serial_icr_write(up, UART_ACR, up->acr);

	return value;
}