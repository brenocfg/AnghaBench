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
typedef  int /*<<< orphan*/  u16 ;
struct wahc {int /*<<< orphan*/  usb_dev; TYPE_1__* usb_iface; } ;
struct usb_rpipe_descriptor {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_DT_RPIPE ; 
 int USB_RECIP_RPIPE ; 
 int /*<<< orphan*/  USB_REQ_SET_DESCRIPTOR ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct usb_rpipe_descriptor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __rpipe_set_descr(struct wahc *wa,
			     struct usb_rpipe_descriptor *descr, u16 index)
{
	ssize_t result;
	struct device *dev = &wa->usb_iface->dev;

	/* we cannot use the usb_get_descriptor() function because the
	 * arguments are different.
	 */
	result = usb_control_msg(
		wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
		USB_REQ_SET_DESCRIPTOR,
		USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_RPIPE,
		USB_DT_RPIPE<<8, index, descr, sizeof(*descr),
		USB_CTRL_SET_TIMEOUT);
	if (result < 0) {
		dev_err(dev, "rpipe %u: set descriptor failed: %d\n",
			index, (int)result);
		goto error;
	}
	if (result < sizeof(*descr)) {
		dev_err(dev, "rpipe %u: sent short descriptor "
			"(%zd vs %zd bytes required)\n",
			index, result, sizeof(*descr));
		result = -EINVAL;
		goto error;
	}
	result = 0;

error:
	return result;

}