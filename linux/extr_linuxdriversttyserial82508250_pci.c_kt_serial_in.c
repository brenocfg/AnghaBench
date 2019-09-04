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
struct uart_port {scalar_t__ iobase; } ;
struct uart_8250_port {unsigned int ier; } ;

/* Variables and functions */
 int UART_IER ; 
 unsigned int inb (scalar_t__) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static unsigned int kt_serial_in(struct uart_port *p, int offset)
{
	struct uart_8250_port *up = up_to_u8250p(p);
	unsigned int val;

	/*
	 * When the Intel ME (management engine) gets reset its serial
	 * port registers could return 0 momentarily.  Functions like
	 * serial8250_console_write, read and save the IER, perform
	 * some operation and then restore it.  In order to avoid
	 * setting IER register inadvertently to 0, if the value read
	 * is 0, double check with ier value in uart_8250_port and use
	 * that instead.  up->ier should be the same value as what is
	 * currently configured.
	 */
	val = inb(p->iobase + offset);
	if (offset == UART_IER) {
		if (val == 0)
			val = up->ier;
	}
	return val;
}