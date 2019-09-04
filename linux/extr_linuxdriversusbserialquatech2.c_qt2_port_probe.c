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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  dev; TYPE_1__** port; } ;
struct qt2_port_private {struct qt2_port_private* write_buffer; int /*<<< orphan*/  write_urb; struct usb_serial_port* port; int /*<<< orphan*/  urb_lock; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  bulk_out_endpointAddress; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QT2_WRITE_BUFFER_SIZE ; 
 int /*<<< orphan*/  kfree (struct qt2_port_private*) ; 
 struct qt2_port_private* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qt2_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qt2_write_bulk_callback ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qt2_port_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct qt2_port_private*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_port_probe(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct qt2_port_private *port_priv;
	u8 bEndpointAddress;

	port_priv = kzalloc(sizeof(*port_priv), GFP_KERNEL);
	if (!port_priv)
		return -ENOMEM;

	spin_lock_init(&port_priv->lock);
	spin_lock_init(&port_priv->urb_lock);
	port_priv->port = port;

	port_priv->write_buffer = kmalloc(QT2_WRITE_BUFFER_SIZE, GFP_KERNEL);
	if (!port_priv->write_buffer)
		goto err_buf;

	port_priv->write_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!port_priv->write_urb)
		goto err_urb;

	bEndpointAddress = serial->port[0]->bulk_out_endpointAddress;
	usb_fill_bulk_urb(port_priv->write_urb, serial->dev,
				usb_sndbulkpipe(serial->dev, bEndpointAddress),
				port_priv->write_buffer,
				QT2_WRITE_BUFFER_SIZE,
				qt2_write_bulk_callback, port);

	usb_set_serial_port_data(port, port_priv);

	return 0;
err_urb:
	kfree(port_priv->write_buffer);
err_buf:
	kfree(port_priv);
	return -ENOMEM;
}