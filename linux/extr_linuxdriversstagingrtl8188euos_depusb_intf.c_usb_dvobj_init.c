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
struct usb_interface_descriptor {int bNumEndpoints; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {TYPE_1__* endpoint; struct usb_interface_descriptor desc; } ;
struct usb_config_descriptor {int /*<<< orphan*/  bNumInterfaces; } ;
struct usb_host_config {struct usb_config_descriptor desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device {scalar_t__ speed; struct usb_host_config* actconfig; } ;
struct dvobj_priv {size_t RtNumInPipes; size_t RtNumOutPipes; int* RtInPipe; int* RtOutPipe; int ishighspeed; int /*<<< orphan*/  usb_vendor_req_mutex; int /*<<< orphan*/  InterfaceNumber; int /*<<< orphan*/  NumInterfaces; struct usb_device* pusbdev; struct usb_interface* pusbintf; } ;
struct TYPE_2__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct dvobj_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct dvobj_priv*) ; 

__attribute__((used)) static struct dvobj_priv *usb_dvobj_init(struct usb_interface *usb_intf)
{
	int	i;
	struct dvobj_priv *pdvobjpriv;
	struct usb_host_config		*phost_conf;
	struct usb_config_descriptor	*pconf_desc;
	struct usb_host_interface	*phost_iface;
	struct usb_interface_descriptor	*piface_desc;
	struct usb_endpoint_descriptor	*pendp_desc;
	struct usb_device	*pusbd;

	pdvobjpriv = kzalloc(sizeof(*pdvobjpriv), GFP_KERNEL);
	if (!pdvobjpriv)
		return NULL;

	pdvobjpriv->pusbintf = usb_intf;
	pusbd = interface_to_usbdev(usb_intf);
	pdvobjpriv->pusbdev = pusbd;
	usb_set_intfdata(usb_intf, pdvobjpriv);

	pdvobjpriv->RtNumInPipes = 0;
	pdvobjpriv->RtNumOutPipes = 0;

	phost_conf = pusbd->actconfig;
	pconf_desc = &phost_conf->desc;

	phost_iface = &usb_intf->altsetting[0];
	piface_desc = &phost_iface->desc;

	pdvobjpriv->NumInterfaces = pconf_desc->bNumInterfaces;
	pdvobjpriv->InterfaceNumber = piface_desc->bInterfaceNumber;

	for (i = 0; i < piface_desc->bNumEndpoints; i++) {
		int ep_num;

		pendp_desc = &phost_iface->endpoint[i].desc;

		ep_num = usb_endpoint_num(pendp_desc);

		if (usb_endpoint_is_bulk_in(pendp_desc)) {
			pdvobjpriv->RtInPipe[pdvobjpriv->RtNumInPipes] = ep_num;
			pdvobjpriv->RtNumInPipes++;
		} else if (usb_endpoint_is_int_in(pendp_desc)) {
			pdvobjpriv->RtInPipe[pdvobjpriv->RtNumInPipes] = ep_num;
			pdvobjpriv->RtNumInPipes++;
		} else if (usb_endpoint_is_bulk_out(pendp_desc)) {
			pdvobjpriv->RtOutPipe[pdvobjpriv->RtNumOutPipes] =
				ep_num;
			pdvobjpriv->RtNumOutPipes++;
		}
	}

	if (pusbd->speed == USB_SPEED_HIGH)
		pdvobjpriv->ishighspeed = true;
	else
		pdvobjpriv->ishighspeed = false;

	mutex_init(&pdvobjpriv->usb_vendor_req_mutex);
	usb_get_dev(pusbd);

	return pdvobjpriv;
}