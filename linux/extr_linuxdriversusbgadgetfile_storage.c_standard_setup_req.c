#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct usb_request {scalar_t__ buf; } ;
struct usb_ctrlrequest {int bRequest; int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct fsg_dev {int new_config; int /*<<< orphan*/  config; TYPE_2__* gadget; TYPE_1__* ep0; struct usb_request* ep0req; } ;
struct TYPE_10__ {int /*<<< orphan*/  bMaxPacketSize0; } ;
struct TYPE_9__ {int /*<<< orphan*/  speed; } ;
struct TYPE_8__ {int /*<<< orphan*/  maxpacket; } ;

/* Variables and functions */
 int CONFIG_VALUE ; 
 int DELAYED_STATUS ; 
 int EDOM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FSG_STATE_CONFIG_CHANGE ; 
 int /*<<< orphan*/  FSG_STATE_INTERFACE_CHANGE ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
#define  USB_DT_BOS 138 
#define  USB_DT_CONFIG 137 
#define  USB_DT_DEVICE 136 
#define  USB_DT_DEVICE_QUALIFIER 135 
#define  USB_DT_OTHER_SPEED_CONFIG 134 
#define  USB_DT_STRING 133 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_INTERFACE ; 
#define  USB_REQ_GET_CONFIGURATION 132 
#define  USB_REQ_GET_DESCRIPTOR 131 
#define  USB_REQ_GET_INTERFACE 130 
#define  USB_REQ_SET_CONFIGURATION 129 
#define  USB_REQ_SET_INTERFACE 128 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  VDBG (struct fsg_dev*,char*,...) ; 
 TYPE_3__ dev_qualifier ; 
 TYPE_3__ device_desc ; 
 int /*<<< orphan*/  fsg_stringtab ; 
 int /*<<< orphan*/  gadget_is_dualspeed (TYPE_2__*) ; 
 int /*<<< orphan*/  gadget_is_superspeed (TYPE_2__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_3__*,int) ; 
 int populate_bos (struct fsg_dev*,scalar_t__) ; 
 int populate_config_buf (TYPE_2__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int usb_gadget_get_string (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int standard_setup_req(struct fsg_dev *fsg,
		const struct usb_ctrlrequest *ctrl)
{
	struct usb_request	*req = fsg->ep0req;
	int			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);

	/* Usually this just stores reply data in the pre-allocated ep0 buffer,
	 * but config change events will also reconfigure hardware. */
	switch (ctrl->bRequest) {

	case USB_REQ_GET_DESCRIPTOR:
		if (ctrl->bRequestType != (USB_DIR_IN | USB_TYPE_STANDARD |
				USB_RECIP_DEVICE))
			break;
		switch (w_value >> 8) {

		case USB_DT_DEVICE:
			VDBG(fsg, "get device descriptor\n");
			device_desc.bMaxPacketSize0 = fsg->ep0->maxpacket;
			value = sizeof device_desc;
			memcpy(req->buf, &device_desc, value);
			break;
		case USB_DT_DEVICE_QUALIFIER:
			VDBG(fsg, "get device qualifier\n");
			if (!gadget_is_dualspeed(fsg->gadget) ||
					fsg->gadget->speed == USB_SPEED_SUPER)
				break;
			/*
			 * Assume ep0 uses the same maxpacket value for both
			 * speeds
			 */
			dev_qualifier.bMaxPacketSize0 = fsg->ep0->maxpacket;
			value = sizeof dev_qualifier;
			memcpy(req->buf, &dev_qualifier, value);
			break;

		case USB_DT_OTHER_SPEED_CONFIG:
			VDBG(fsg, "get other-speed config descriptor\n");
			if (!gadget_is_dualspeed(fsg->gadget) ||
					fsg->gadget->speed == USB_SPEED_SUPER)
				break;
			goto get_config;
		case USB_DT_CONFIG:
			VDBG(fsg, "get configuration descriptor\n");
get_config:
			value = populate_config_buf(fsg->gadget,
					req->buf,
					w_value >> 8,
					w_value & 0xff);
			break;

		case USB_DT_STRING:
			VDBG(fsg, "get string descriptor\n");

			/* wIndex == language code */
			value = usb_gadget_get_string(&fsg_stringtab,
					w_value & 0xff, req->buf);
			break;

		case USB_DT_BOS:
			VDBG(fsg, "get bos descriptor\n");

			if (gadget_is_superspeed(fsg->gadget))
				value = populate_bos(fsg, req->buf);
			break;
		}

		break;

	/* One config, two speeds */
	case USB_REQ_SET_CONFIGURATION:
		if (ctrl->bRequestType != (USB_DIR_OUT | USB_TYPE_STANDARD |
				USB_RECIP_DEVICE))
			break;
		VDBG(fsg, "set configuration\n");
		if (w_value == CONFIG_VALUE || w_value == 0) {
			fsg->new_config = w_value;

			/* Raise an exception to wipe out previous transaction
			 * state (queued bufs, etc) and set the new config. */
			raise_exception(fsg, FSG_STATE_CONFIG_CHANGE);
			value = DELAYED_STATUS;
		}
		break;
	case USB_REQ_GET_CONFIGURATION:
		if (ctrl->bRequestType != (USB_DIR_IN | USB_TYPE_STANDARD |
				USB_RECIP_DEVICE))
			break;
		VDBG(fsg, "get configuration\n");
		*(u8 *) req->buf = fsg->config;
		value = 1;
		break;

	case USB_REQ_SET_INTERFACE:
		if (ctrl->bRequestType != (USB_DIR_OUT| USB_TYPE_STANDARD |
				USB_RECIP_INTERFACE))
			break;
		if (fsg->config && w_index == 0) {

			/* Raise an exception to wipe out previous transaction
			 * state (queued bufs, etc) and install the new
			 * interface altsetting. */
			raise_exception(fsg, FSG_STATE_INTERFACE_CHANGE);
			value = DELAYED_STATUS;
		}
		break;
	case USB_REQ_GET_INTERFACE:
		if (ctrl->bRequestType != (USB_DIR_IN | USB_TYPE_STANDARD |
				USB_RECIP_INTERFACE))
			break;
		if (!fsg->config)
			break;
		if (w_index != 0) {
			value = -EDOM;
			break;
		}
		VDBG(fsg, "get interface\n");
		*(u8 *) req->buf = 0;
		value = 1;
		break;

	default:
		VDBG(fsg,
			"unknown control req %02x.%02x v%04x i%04x l%u\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, le16_to_cpu(ctrl->wLength));
	}

	return value;
}