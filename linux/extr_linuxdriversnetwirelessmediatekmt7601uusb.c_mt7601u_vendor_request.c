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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MT7601U_STATE_REMOVED ; 
 int MT_VEND_REQ_MAX_RETRY ; 
 int /*<<< orphan*/  MT_VEND_REQ_TOUT_MS ; 
 int const USB_DIR_IN ; 
 int const USB_RECIP_DEVICE ; 
 int const USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int const,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct usb_device* mt7601u_to_usb_dev (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mt_vend_req (struct mt7601u_dev*,unsigned int const,int const,int const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void*,size_t const,int) ; 
 int usb_control_msg (struct usb_device*,unsigned int const,int const,int const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void*,size_t const,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int mt7601u_vendor_request(struct mt7601u_dev *dev, const u8 req,
			   const u8 direction, const u16 val, const u16 offset,
			   void *buf, const size_t buflen)
{
	int i, ret;
	struct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	const u8 req_type = direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	const unsigned int pipe = (direction == USB_DIR_IN) ?
		usb_rcvctrlpipe(usb_dev, 0) : usb_sndctrlpipe(usb_dev, 0);

	for (i = 0; i < MT_VEND_REQ_MAX_RETRY; i++) {
		ret = usb_control_msg(usb_dev, pipe, req, req_type,
				      val, offset, buf, buflen,
				      MT_VEND_REQ_TOUT_MS);
		trace_mt_vend_req(dev, pipe, req, req_type, val, offset,
				  buf, buflen, ret);

		if (ret == -ENODEV)
			set_bit(MT7601U_STATE_REMOVED, &dev->state);
		if (ret >= 0 || ret == -ENODEV)
			return ret;

		msleep(5);
	}

	dev_err(dev->dev, "Vendor request req:%02x off:%04x failed:%d\n",
		req, offset, ret);

	return ret;
}