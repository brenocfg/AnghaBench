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
struct uart_port {int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dev; int /*<<< orphan*/ * membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_uart_release_port(struct uart_port *port)
{
	devm_iounmap(port->dev, port->membase);
	port->membase = NULL;
	devm_release_mem_region(port->dev, port->mapbase, port->mapsize);
}