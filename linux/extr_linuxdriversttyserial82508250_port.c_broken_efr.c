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
 int autoconfig_read_divisor_id (struct uart_8250_port*) ; 
 int size_fifo (struct uart_8250_port*) ; 

__attribute__((used)) static int broken_efr(struct uart_8250_port *up)
{
	/*
	 * Exar ST16C2550 "A2" devices incorrectly detect as
	 * having an EFR, and report an ID of 0x0201.  See
	 * http://linux.derkeiler.com/Mailing-Lists/Kernel/2004-11/4812.html
	 */
	if (autoconfig_read_divisor_id(up) == 0x0201 && size_fifo(up) == 16)
		return 1;

	return 0;
}