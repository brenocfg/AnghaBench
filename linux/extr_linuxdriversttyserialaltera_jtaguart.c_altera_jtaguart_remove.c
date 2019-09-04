#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  membase; } ;
struct platform_device {int id; } ;
struct TYPE_2__ {struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  altera_jtaguart_driver ; 
 TYPE_1__* altera_jtaguart_ports ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int altera_jtaguart_remove(struct platform_device *pdev)
{
	struct uart_port *port;
	int i = pdev->id;

	if (i == -1)
		i = 0;

	port = &altera_jtaguart_ports[i].port;
	uart_remove_one_port(&altera_jtaguart_driver, port);
	iounmap(port->membase);

	return 0;
}