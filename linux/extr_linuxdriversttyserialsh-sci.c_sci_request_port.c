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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  mapbase; } ;
struct sci_port {int /*<<< orphan*/  reg_size; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sci_remap_port (struct uart_port*) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sci_request_port(struct uart_port *port)
{
	struct resource *res;
	struct sci_port *sport = to_sci_port(port);
	int ret;

	res = request_mem_region(port->mapbase, sport->reg_size,
				 dev_name(port->dev));
	if (unlikely(res == NULL)) {
		dev_err(port->dev, "request_mem_region failed.");
		return -EBUSY;
	}

	ret = sci_remap_port(port);
	if (unlikely(ret != 0)) {
		release_resource(res);
		return ret;
	}

	return 0;
}