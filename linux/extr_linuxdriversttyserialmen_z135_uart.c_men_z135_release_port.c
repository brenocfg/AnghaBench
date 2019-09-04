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
struct uart_port {int /*<<< orphan*/ * membase; } ;
struct men_z135_port {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcb_release_mem (int /*<<< orphan*/ ) ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 

__attribute__((used)) static void men_z135_release_port(struct uart_port *port)
{
	struct men_z135_port *uart = to_men_z135(port);

	iounmap(port->membase);
	port->membase = NULL;

	mcb_release_mem(uart->mem);
}