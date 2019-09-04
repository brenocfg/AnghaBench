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
struct tcpm_port {int /*<<< orphan*/  wq; int /*<<< orphan*/  role_sw; int /*<<< orphan*/  typec_port; int /*<<< orphan*/ * port_altmode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_debugfs_exit (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_reset_port (struct tcpm_port*) ; 
 int /*<<< orphan*/  typec_unregister_altmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_role_switch_put (int /*<<< orphan*/ ) ; 

void tcpm_unregister_port(struct tcpm_port *port)
{
	int i;

	tcpm_reset_port(port);
	for (i = 0; i < ARRAY_SIZE(port->port_altmode); i++)
		typec_unregister_altmode(port->port_altmode[i]);
	typec_unregister_port(port->typec_port);
	usb_role_switch_put(port->role_sw);
	tcpm_debugfs_exit(port);
	destroy_workqueue(port->wq);
}