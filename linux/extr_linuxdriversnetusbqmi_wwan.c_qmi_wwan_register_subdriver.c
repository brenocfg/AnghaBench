#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_2__* status; int /*<<< orphan*/  data; } ;
struct usb_driver {int dummy; } ;
struct qmi_wwan_state {struct usb_driver* subdriver; TYPE_3__* control; int /*<<< orphan*/  pmcount; TYPE_3__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; TYPE_1__* cur_altsetting; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc; } ;
struct TYPE_5__ {TYPE_2__* endpoint; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct usb_driver*) ; 
 int PTR_ERR (struct usb_driver*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qmi_wwan_cdc_wdm_manage_power ; 
 struct usb_driver* usb_cdc_wdm_register (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int usbnet_get_endpoints (struct usbnet*,TYPE_3__*) ; 

__attribute__((used)) static int qmi_wwan_register_subdriver(struct usbnet *dev)
{
	int rv;
	struct usb_driver *subdriver = NULL;
	struct qmi_wwan_state *info = (void *)&dev->data;

	/* collect bulk endpoints */
	rv = usbnet_get_endpoints(dev, info->data);
	if (rv < 0)
		goto err;

	/* update status endpoint if separate control interface */
	if (info->control != info->data)
		dev->status = &info->control->cur_altsetting->endpoint[0];

	/* require interrupt endpoint for subdriver */
	if (!dev->status) {
		rv = -EINVAL;
		goto err;
	}

	/* for subdriver power management */
	atomic_set(&info->pmcount, 0);

	/* register subdriver */
	subdriver = usb_cdc_wdm_register(info->control, &dev->status->desc,
					 4096, &qmi_wwan_cdc_wdm_manage_power);
	if (IS_ERR(subdriver)) {
		dev_err(&info->control->dev, "subdriver registration failed\n");
		rv = PTR_ERR(subdriver);
		goto err;
	}

	/* prevent usbnet from using status endpoint */
	dev->status = NULL;

	/* save subdriver struct for suspend/resume wrappers */
	info->subdriver = subdriver;

err:
	return rv;
}