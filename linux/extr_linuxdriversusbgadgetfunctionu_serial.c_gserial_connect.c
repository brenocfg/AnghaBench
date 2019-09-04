#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct gserial {TYPE_2__* in; int /*<<< orphan*/  (* disconnect ) (struct gserial*) ;int /*<<< orphan*/  (* connect ) (struct gserial*) ;int /*<<< orphan*/  port_line_coding; struct gs_port* ioport; TYPE_2__* out; } ;
struct TYPE_5__ {scalar_t__ count; } ;
struct gs_port {int /*<<< orphan*/  port_lock; int /*<<< orphan*/  port_num; TYPE_1__ port; int /*<<< orphan*/  port_line_coding; struct gserial* port_usb; } ;
struct TYPE_7__ {struct gs_port* port; } ;
struct TYPE_6__ {struct gs_port* driver_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 size_t MAX_U_SERIAL_PORTS ; 
 int gs_console_connect (size_t) ; 
 int /*<<< orphan*/  gs_start_io (struct gs_port*) ; 
 TYPE_4__* ports ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gserial*) ; 
 int /*<<< orphan*/  stub2 (struct gserial*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_2__*) ; 
 int usb_ep_enable (TYPE_2__*) ; 

int gserial_connect(struct gserial *gser, u8 port_num)
{
	struct gs_port	*port;
	unsigned long	flags;
	int		status;

	if (port_num >= MAX_U_SERIAL_PORTS)
		return -ENXIO;

	port = ports[port_num].port;
	if (!port) {
		pr_err("serial line %d not allocated.\n", port_num);
		return -EINVAL;
	}
	if (port->port_usb) {
		pr_err("serial line %d is in use.\n", port_num);
		return -EBUSY;
	}

	/* activate the endpoints */
	status = usb_ep_enable(gser->in);
	if (status < 0)
		return status;
	gser->in->driver_data = port;

	status = usb_ep_enable(gser->out);
	if (status < 0)
		goto fail_out;
	gser->out->driver_data = port;

	/* then tell the tty glue that I/O can work */
	spin_lock_irqsave(&port->port_lock, flags);
	gser->ioport = port;
	port->port_usb = gser;

	/* REVISIT unclear how best to handle this state...
	 * we don't really couple it with the Linux TTY.
	 */
	gser->port_line_coding = port->port_line_coding;

	/* REVISIT if waiting on "carrier detect", signal. */

	/* if it's already open, start I/O ... and notify the serial
	 * protocol about open/close status (connect/disconnect).
	 */
	if (port->port.count) {
		pr_debug("gserial_connect: start ttyGS%d\n", port->port_num);
		gs_start_io(port);
		if (gser->connect)
			gser->connect(gser);
	} else {
		if (gser->disconnect)
			gser->disconnect(gser);
	}

	status = gs_console_connect(port_num);
	spin_unlock_irqrestore(&port->port_lock, flags);

	return status;

fail_out:
	usb_ep_disable(gser->in);
	return status;
}