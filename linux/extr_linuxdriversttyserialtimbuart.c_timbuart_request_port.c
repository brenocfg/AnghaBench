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
struct uart_port {int flags; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int UPF_IOREMAP ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int resource_size (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timbuart_request_port(struct uart_port *port)
{
	struct platform_device *pdev = to_platform_device(port->dev);
	int size =
		resource_size(platform_get_resource(pdev, IORESOURCE_MEM, 0));

	if (!request_mem_region(port->mapbase, size, "timb-uart"))
		return -EBUSY;

	if (port->flags & UPF_IOREMAP) {
		port->membase = ioremap(port->mapbase, size);
		if (port->membase == NULL) {
			release_mem_region(port->mapbase, size);
			return -ENOMEM;
		}
	}

	return 0;
}