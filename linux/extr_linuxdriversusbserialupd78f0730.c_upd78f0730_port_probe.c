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
struct upd78f0730_port_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct upd78f0730_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct upd78f0730_port_private*) ; 

__attribute__((used)) static int upd78f0730_port_probe(struct usb_serial_port *port)
{
	struct upd78f0730_port_private *private;

	private = kzalloc(sizeof(*private), GFP_KERNEL);
	if (!private)
		return -ENOMEM;

	mutex_init(&private->lock);
	usb_set_serial_port_data(port, private);

	return 0;
}