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

/* Variables and functions */
 char uart_recv () ; 
 int /*<<< orphan*/  uart_send (char) ; 
 int /*<<< orphan*/  uart_send_string (char*) ; 

void handle_uart_irq( void ) 
{
	char c = uart_recv();
	uart_send_string("mini UART interrupt received. Received: ");
	uart_send(c);
	uart_send_string("\n\r");
}