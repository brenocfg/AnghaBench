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
struct usb_serial_port {int dummy; } ;
struct edgeport_port {struct usb_serial_port* port; int /*<<< orphan*/  ep_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct edgeport_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct edgeport_port*) ; 

__attribute__((used)) static int edge_port_probe(struct usb_serial_port *port)
{
	struct edgeport_port *edge_port;

	edge_port = kzalloc(sizeof(*edge_port), GFP_KERNEL);
	if (!edge_port)
		return -ENOMEM;

	spin_lock_init(&edge_port->ep_lock);
	edge_port->port = port;

	usb_set_serial_port_data(port, edge_port);

	return 0;
}