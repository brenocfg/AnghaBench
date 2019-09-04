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
struct zd1201 {int /*<<< orphan*/  endp_out2; int /*<<< orphan*/  usb; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ZD1201_USB_CMDREQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct zd1201*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd1201_usbfree ; 

__attribute__((used)) static int zd1201_docmd(struct zd1201 *zd, int cmd, int parm0,
			int parm1, int parm2)
{
	unsigned char *command;
	int ret;
	struct urb *urb;

	command = kmalloc(16, GFP_ATOMIC);
	if (!command)
		return -ENOMEM;

	*((__le32*)command) = cpu_to_le32(ZD1201_USB_CMDREQ);
	*((__le16*)&command[4]) = cpu_to_le16(cmd);
	*((__le16*)&command[6]) = cpu_to_le16(parm0);
	*((__le16*)&command[8]) = cpu_to_le16(parm1);
	*((__le16*)&command[10])= cpu_to_le16(parm2);

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		kfree(command);
		return -ENOMEM;
	}
	usb_fill_bulk_urb(urb, zd->usb, usb_sndbulkpipe(zd->usb, zd->endp_out2),
			  command, 16, zd1201_usbfree, zd);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret) {
		kfree(command);
		usb_free_urb(urb);
	}

	return ret;
}