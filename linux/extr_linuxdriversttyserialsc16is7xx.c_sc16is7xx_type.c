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
struct uart_port {scalar_t__ type; int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {TYPE_1__* devtype; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 scalar_t__ PORT_SC16IS7XX ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *sc16is7xx_type(struct uart_port *port)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);

	return (port->type == PORT_SC16IS7XX) ? s->devtype->name : NULL;
}