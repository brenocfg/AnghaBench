#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {TYPE_2__* dev; } ;
struct kobil_private {int device_type; scalar_t__ cur_pos; scalar_t__ filled; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  KOBIL_ADAPTER_B_PRODUCT_ID 131 
#define  KOBIL_ADAPTER_K_PRODUCT_ID 130 
#define  KOBIL_KAAN_SIM_PRODUCT_ID 129 
#define  KOBIL_USBTWIN_PRODUCT_ID 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct kobil_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct kobil_private*) ; 

__attribute__((used)) static int kobil_port_probe(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct kobil_private *priv;

	priv = kmalloc(sizeof(struct kobil_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->filled = 0;
	priv->cur_pos = 0;
	priv->device_type = le16_to_cpu(serial->dev->descriptor.idProduct);

	switch (priv->device_type) {
	case KOBIL_ADAPTER_B_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL B1 PRO / KAAN PRO detected\n");
		break;
	case KOBIL_ADAPTER_K_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL KAAN Standard Plus / SecOVID Reader Plus detected\n");
		break;
	case KOBIL_USBTWIN_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL USBTWIN detected\n");
		break;
	case KOBIL_KAAN_SIM_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL KAAN SIM detected\n");
		break;
	}
	usb_set_serial_port_data(port, priv);

	return 0;
}