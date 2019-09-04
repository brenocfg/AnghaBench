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
struct tty_port {struct serdev_controller* client_data; int /*<<< orphan*/ * client_ops; } ;
struct serport {int dummy; } ;
struct serdev_controller {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  serdev_controller_put (struct serdev_controller*) ; 
 int /*<<< orphan*/  serdev_controller_remove (struct serdev_controller*) ; 

int serdev_tty_port_unregister(struct tty_port *port)
{
	struct serdev_controller *ctrl = port->client_data;
	struct serport *serport = serdev_controller_get_drvdata(ctrl);

	if (!serport)
		return -ENODEV;

	serdev_controller_remove(ctrl);
	port->client_ops = NULL;
	port->client_data = NULL;
	serdev_controller_put(ctrl);

	return 0;
}