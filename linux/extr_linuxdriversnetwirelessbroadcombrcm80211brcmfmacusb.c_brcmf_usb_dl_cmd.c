#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_5__ {int bRequestType; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  wLength; } ;
struct brcmf_usbdev_info {int ctl_completed; TYPE_2__* ctl_urb; TYPE_1__ ctl_read; int /*<<< orphan*/  usbdev; } ;
struct TYPE_6__ {int transfer_buffer_length; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_usb_ioctl_resp_wait (struct brcmf_usbdev_info*) ; 
 scalar_t__ brcmf_usb_sync_complete ; 
 int /*<<< orphan*/  cpu_to_le16p (int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,void*,int,int /*<<< orphan*/ ,struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_usb_dl_cmd(struct brcmf_usbdev_info *devinfo, u8 cmd,
			    void *buffer, int buflen)
{
	int ret;
	char *tmpbuf;
	u16 size;

	if ((!devinfo) || (devinfo->ctl_urb == NULL))
		return -EINVAL;

	tmpbuf = kmalloc(buflen, GFP_ATOMIC);
	if (!tmpbuf)
		return -ENOMEM;

	size = buflen;
	devinfo->ctl_urb->transfer_buffer_length = size;

	devinfo->ctl_read.wLength = cpu_to_le16p(&size);
	devinfo->ctl_read.bRequestType = USB_DIR_IN | USB_TYPE_VENDOR |
		USB_RECIP_INTERFACE;
	devinfo->ctl_read.bRequest = cmd;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		usb_rcvctrlpipe(devinfo->usbdev, 0),
		(unsigned char *) &devinfo->ctl_read,
		(void *) tmpbuf, size,
		(usb_complete_t)brcmf_usb_sync_complete, devinfo);

	devinfo->ctl_completed = false;
	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	if (ret < 0) {
		brcmf_err("usb_submit_urb failed %d\n", ret);
		goto finalize;
	}

	if (!brcmf_usb_ioctl_resp_wait(devinfo)) {
		usb_kill_urb(devinfo->ctl_urb);
		ret = -ETIMEDOUT;
	} else {
		memcpy(buffer, tmpbuf, buflen);
	}

finalize:
	kfree(tmpbuf);
	return ret;
}