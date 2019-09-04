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
struct uart_port {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct uart_port port; } ;

/* Variables and functions */
 int MCF_MAXPORTS ; 
 int /*<<< orphan*/  mcf_driver ; 
 TYPE_1__* mcf_ports ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int mcf_remove(struct platform_device *pdev)
{
	struct uart_port *port;
	int i;

	for (i = 0; (i < MCF_MAXPORTS); i++) {
		port = &mcf_ports[i].port;
		if (port)
			uart_remove_one_port(&mcf_driver, port);
	}

	return 0;
}