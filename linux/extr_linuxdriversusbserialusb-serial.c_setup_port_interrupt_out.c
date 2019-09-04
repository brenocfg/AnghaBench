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
struct usb_serial_port {int interrupt_out_size; int /*<<< orphan*/  interrupt_out_buffer; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_out_endpointAddress; TYPE_1__* serial; } ;
struct usb_serial_driver {int /*<<< orphan*/  write_int_callback; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* dev; struct usb_serial_driver* type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_port_interrupt_out(struct usb_serial_port *port,
					struct usb_endpoint_descriptor *epd)
{
	struct usb_serial_driver *type = port->serial->type;
	struct usb_device *udev = port->serial->dev;
	int buffer_size;

	port->interrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!port->interrupt_out_urb)
		return -ENOMEM;
	buffer_size = usb_endpoint_maxp(epd);
	port->interrupt_out_size = buffer_size;
	port->interrupt_out_endpointAddress = epd->bEndpointAddress;
	port->interrupt_out_buffer = kmalloc(buffer_size, GFP_KERNEL);
	if (!port->interrupt_out_buffer)
		return -ENOMEM;
	usb_fill_int_urb(port->interrupt_out_urb, udev,
			usb_sndintpipe(udev, epd->bEndpointAddress),
			port->interrupt_out_buffer, buffer_size,
			type->write_int_callback, port,
			epd->bInterval);

	return 0;
}