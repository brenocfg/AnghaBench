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
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  interrupt_in_urb; } ;
struct cyberjack_private {scalar_t__ wrsent; scalar_t__ wrfilled; scalar_t__ rdtodo; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct cyberjack_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct cyberjack_private*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyberjack_port_probe(struct usb_serial_port *port)
{
	struct cyberjack_private *priv;
	int result;

	priv = kmalloc(sizeof(struct cyberjack_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->rdtodo = 0;
	priv->wrfilled = 0;
	priv->wrsent = 0;

	usb_set_serial_port_data(port, priv);

	result = usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL);
	if (result)
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");

	return 0;
}