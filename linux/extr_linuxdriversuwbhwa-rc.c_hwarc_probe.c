#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uwb_rc {int /*<<< orphan*/ * filter_event; int /*<<< orphan*/ * filter_cmd; int /*<<< orphan*/  reset; int /*<<< orphan*/  cmd; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;
struct usb_interface {TYPE_3__* cur_altsetting; struct device dev; } ;
struct usb_device_id {int driver_info; } ;
struct hwarc {int /*<<< orphan*/  usb_dev; struct uwb_rc* uwb_rc; int /*<<< orphan*/  usb_iface; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int WUSB_QUIRK_WHCI_CMD_EVT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  hwarc_cmd ; 
 int /*<<< orphan*/ * hwarc_filter_cmd ; 
 int /*<<< orphan*/ * hwarc_filter_event ; 
 int hwarc_get_version (struct uwb_rc*) ; 
 int /*<<< orphan*/  hwarc_init (struct hwarc*) ; 
 int /*<<< orphan*/  hwarc_neep_init ; 
 int /*<<< orphan*/  hwarc_neep_release ; 
 int /*<<< orphan*/  hwarc_reset ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct hwarc*) ; 
 struct hwarc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct hwarc*) ; 
 int uwb_rc_add (struct uwb_rc*,struct device*,struct hwarc*) ; 
 struct uwb_rc* uwb_rc_alloc () ; 
 int /*<<< orphan*/  uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_rm (struct uwb_rc*) ; 

__attribute__((used)) static int hwarc_probe(struct usb_interface *iface,
		       const struct usb_device_id *id)
{
	int result;
	struct uwb_rc *uwb_rc;
	struct hwarc *hwarc;
	struct device *dev = &iface->dev;

	if (iface->cur_altsetting->desc.bNumEndpoints < 1)
		return -ENODEV;
	if (!usb_endpoint_xfer_int(&iface->cur_altsetting->endpoint[0].desc))
		return -ENODEV;

	result = -ENOMEM;
	uwb_rc = uwb_rc_alloc();
	if (uwb_rc == NULL) {
		dev_err(dev, "unable to allocate RC instance\n");
		goto error_rc_alloc;
	}
	hwarc = kzalloc(sizeof(*hwarc), GFP_KERNEL);
	if (hwarc == NULL) {
		dev_err(dev, "unable to allocate HWA RC instance\n");
		goto error_alloc;
	}
	hwarc_init(hwarc);
	hwarc->usb_dev = usb_get_dev(interface_to_usbdev(iface));
	hwarc->usb_iface = usb_get_intf(iface);
	hwarc->uwb_rc = uwb_rc;

	uwb_rc->owner = THIS_MODULE;
	uwb_rc->start = hwarc_neep_init;
	uwb_rc->stop  = hwarc_neep_release;
	uwb_rc->cmd   = hwarc_cmd;
	uwb_rc->reset = hwarc_reset;
	if (id->driver_info & WUSB_QUIRK_WHCI_CMD_EVT) {
		uwb_rc->filter_cmd   = NULL;
		uwb_rc->filter_event = NULL;
	} else {
		uwb_rc->filter_cmd   = hwarc_filter_cmd;
		uwb_rc->filter_event = hwarc_filter_event;
	}

	result = uwb_rc_add(uwb_rc, dev, hwarc);
	if (result < 0)
		goto error_rc_add;
	result = hwarc_get_version(uwb_rc);
	if (result < 0) {
		dev_err(dev, "cannot retrieve version of RC \n");
		goto error_get_version;
	}
	usb_set_intfdata(iface, hwarc);
	return 0;

error_get_version:
	uwb_rc_rm(uwb_rc);
error_rc_add:
	usb_put_intf(iface);
	usb_put_dev(hwarc->usb_dev);
	kfree(hwarc);
error_alloc:
	uwb_rc_put(uwb_rc);
error_rc_alloc:
	return result;
}