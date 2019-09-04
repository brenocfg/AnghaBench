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
struct uart_port {int fifosize; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_GET_CHAR (struct uart_port*) ; 

__attribute__((used)) static void apbuart_flush_fifo(struct uart_port *port)
{
	int i;

	for (i = 0; i < port->fifosize; i++)
		UART_GET_CHAR(port);
}