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
struct TYPE_2__ {struct vcc_port* name; } ;
struct vcc_port {struct vcc_port* domain; TYPE_1__ vio; scalar_t__ removed; int /*<<< orphan*/ * tty; } ;
struct tty_struct {struct vcc_port* port; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vcc_port*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tty_port_destroy (struct vcc_port*) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 int /*<<< orphan*/  vcc_table_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcc_cleanup(struct tty_struct *tty)
{
	struct vcc_port *port;

	if (unlikely(!tty)) {
		pr_err("VCC: cleanup: Invalid TTY handle\n");
		return;
	}

	port = vcc_get(tty->index, true);
	if (port) {
		port->tty = NULL;

		if (port->removed) {
			vcc_table_remove(tty->index);
			kfree(port->vio.name);
			kfree(port->domain);
			kfree(port);
		} else {
			vcc_put(port, true);
		}
	}

	tty_port_destroy(tty->port);
	kfree(tty->port);
	tty->port = NULL;
}