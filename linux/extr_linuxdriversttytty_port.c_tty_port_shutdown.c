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
struct tty_struct {int dummy; } ;
struct tty_port {int /*<<< orphan*/  mutex; TYPE_1__* ops; scalar_t__ console; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct tty_port*) ;} ;

/* Variables and functions */
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_port*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_lower_dtr_rts (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (struct tty_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tty_port_shutdown(struct tty_port *port, struct tty_struct *tty)
{
	mutex_lock(&port->mutex);
	if (port->console)
		goto out;

	if (tty_port_initialized(port)) {
		tty_port_set_initialized(port, 0);
		/*
		 * Drop DTR/RTS if HUPCL is set. This causes any attached
		 * modem to hang up the line.
		 */
		if (tty && C_HUPCL(tty))
			tty_port_lower_dtr_rts(port);

		if (port->ops->shutdown)
			port->ops->shutdown(port);
	}
out:
	mutex_unlock(&port->mutex);
}