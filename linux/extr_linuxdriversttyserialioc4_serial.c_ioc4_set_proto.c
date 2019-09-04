#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ioc4_port {TYPE_2__* ip_mem; struct hooks* ip_hooks; } ;
struct hooks {size_t rs422_select_pin; } ;
struct TYPE_4__ {TYPE_1__* gppr; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
#define  PROTO_RS232 129 
#define  PROTO_RS422 128 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioc4_set_proto(struct ioc4_port *port, int proto)
{
	struct hooks *hooks = port->ip_hooks;

	switch (proto) {
	case PROTO_RS232:
		/* Clear the appropriate GIO pin */
		writel(0, (&port->ip_mem->gppr[hooks->rs422_select_pin].raw));
		break;

	case PROTO_RS422:
		/* Set the appropriate GIO pin */
		writel(1, (&port->ip_mem->gppr[hooks->rs422_select_pin].raw));
		break;

	default:
		return 1;
	}
	return 0;
}