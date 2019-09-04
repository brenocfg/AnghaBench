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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  port_number; struct usb_serial* serial; } ;
struct usb_serial {int num_ports; } ;
struct sierra_port_private {int /*<<< orphan*/  num_out_urbs; int /*<<< orphan*/  num_in_urbs; int /*<<< orphan*/  delayed; int /*<<< orphan*/  active; int /*<<< orphan*/  lock; } ;
struct sierra_iface_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  N_IN_URB ; 
 int /*<<< orphan*/  N_IN_URB_HM ; 
 int /*<<< orphan*/  N_OUT_URB ; 
 int /*<<< orphan*/  N_OUT_URB_HM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 scalar_t__ is_himemory (int /*<<< orphan*/ ,struct sierra_iface_info const*) ; 
 struct sierra_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sierra_interface_num (struct usb_serial*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct sierra_iface_info typeA_interface_list ; 
 struct sierra_iface_info typeB_interface_list ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct sierra_port_private*) ; 

__attribute__((used)) static int sierra_port_probe(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct sierra_port_private *portdata;
	const struct sierra_iface_info *himemoryp;
	u8 ifnum;

	portdata = kzalloc(sizeof(*portdata), GFP_KERNEL);
	if (!portdata)
		return -ENOMEM;

	spin_lock_init(&portdata->lock);
	init_usb_anchor(&portdata->active);
	init_usb_anchor(&portdata->delayed);

	/* Assume low memory requirements */
	portdata->num_out_urbs = N_OUT_URB;
	portdata->num_in_urbs  = N_IN_URB;

	/* Determine actual memory requirements */
	if (serial->num_ports == 1) {
		/* Get interface number for composite device */
		ifnum = sierra_interface_num(serial);
		himemoryp = &typeB_interface_list;
	} else {
		/* This is really the usb-serial port number of the interface
		 * rather than the interface number.
		 */
		ifnum = port->port_number;
		himemoryp = &typeA_interface_list;
	}

	if (is_himemory(ifnum, himemoryp)) {
		portdata->num_out_urbs = N_OUT_URB_HM;
		portdata->num_in_urbs  = N_IN_URB_HM;
	}

	dev_dbg(&port->dev,
			"Memory usage (urbs) interface #%d, in=%d, out=%d\n",
			ifnum, portdata->num_in_urbs, portdata->num_out_urbs);

	usb_set_serial_port_data(port, portdata);

	return 0;
}