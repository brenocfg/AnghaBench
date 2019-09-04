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
struct metrousb_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct metrousb_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct metrousb_private*) ; 

__attribute__((used)) static int metrousb_port_probe(struct usb_serial_port *port)
{
	struct metrousb_private *metro_priv;

	metro_priv = kzalloc(sizeof(*metro_priv), GFP_KERNEL);
	if (!metro_priv)
		return -ENOMEM;

	spin_lock_init(&metro_priv->lock);

	usb_set_serial_port_data(port, metro_priv);

	return 0;
}