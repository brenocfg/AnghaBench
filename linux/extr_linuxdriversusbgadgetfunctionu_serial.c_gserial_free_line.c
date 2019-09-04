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
struct gs_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct gs_port* port; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gs_tty_driver ; 
 int /*<<< orphan*/  gserial_console_exit () ; 
 int /*<<< orphan*/  gserial_free_port (struct gs_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* ports ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,unsigned char) ; 

void gserial_free_line(unsigned char port_num)
{
	struct gs_port	*port;

	mutex_lock(&ports[port_num].lock);
	if (WARN_ON(!ports[port_num].port)) {
		mutex_unlock(&ports[port_num].lock);
		return;
	}
	port = ports[port_num].port;
	ports[port_num].port = NULL;
	mutex_unlock(&ports[port_num].lock);

	gserial_free_port(port);
	tty_unregister_device(gs_tty_driver, port_num);
	gserial_console_exit();
}