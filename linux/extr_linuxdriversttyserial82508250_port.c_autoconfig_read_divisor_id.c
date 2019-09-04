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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_CONF_MODE_A ; 
 unsigned int serial_dl_read (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_dl_write (struct uart_8250_port*,unsigned int) ; 
 unsigned char serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static unsigned int autoconfig_read_divisor_id(struct uart_8250_port *p)
{
	unsigned char old_lcr;
	unsigned int id, old_dl;

	old_lcr = serial_in(p, UART_LCR);
	serial_out(p, UART_LCR, UART_LCR_CONF_MODE_A);
	old_dl = serial_dl_read(p);
	serial_dl_write(p, 0);
	id = serial_dl_read(p);
	serial_dl_write(p, old_dl);

	serial_out(p, UART_LCR, old_lcr);

	return id;
}