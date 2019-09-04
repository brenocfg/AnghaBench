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
struct usb_serial_port {TYPE_1__* serial; } ;
struct ch341_private {int lcr; int /*<<< orphan*/  baud_rate; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CH341_LCR_CS8 ; 
 int CH341_LCR_ENABLE_RX ; 
 int CH341_LCR_ENABLE_TX ; 
 int /*<<< orphan*/  DEFAULT_BAUD_RATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_configure (int /*<<< orphan*/ ,struct ch341_private*) ; 
 int /*<<< orphan*/  kfree (struct ch341_private*) ; 
 struct ch341_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct ch341_private*) ; 

__attribute__((used)) static int ch341_port_probe(struct usb_serial_port *port)
{
	struct ch341_private *priv;
	int r;

	priv = kzalloc(sizeof(struct ch341_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->baud_rate = DEFAULT_BAUD_RATE;
	/*
	 * Some CH340 devices appear unable to change the initial LCR
	 * settings, so set a sane 8N1 default.
	 */
	priv->lcr = CH341_LCR_ENABLE_RX | CH341_LCR_ENABLE_TX | CH341_LCR_CS8;

	r = ch341_configure(port->serial->dev, priv);
	if (r < 0)
		goto error;

	usb_set_serial_port_data(port, priv);
	return 0;

error:	kfree(priv);
	return r;
}