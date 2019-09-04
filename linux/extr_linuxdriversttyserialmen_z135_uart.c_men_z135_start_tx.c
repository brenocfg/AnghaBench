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
struct uart_port {int dummy; } ;
struct men_z135_port {scalar_t__ automode; } ;

/* Variables and functions */
 int /*<<< orphan*/  men_z135_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  men_z135_handle_tx (struct men_z135_port*) ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 

__attribute__((used)) static void men_z135_start_tx(struct uart_port *port)
{
	struct men_z135_port *uart = to_men_z135(port);

	if (uart->automode)
		men_z135_disable_ms(port);

	men_z135_handle_tx(uart);
}