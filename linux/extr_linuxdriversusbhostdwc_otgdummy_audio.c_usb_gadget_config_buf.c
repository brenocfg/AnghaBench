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
typedef  int /*<<< orphan*/  u8 ;
struct usb_descriptor_header {int dummy; } ;
struct usb_config_descriptor {unsigned int bLength; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_ONE ; 
 int /*<<< orphan*/  USB_DT_CONFIG ; 
 unsigned int USB_DT_CONFIG_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int usb_descriptor_fillbuf (int /*<<< orphan*/ *,unsigned int,struct usb_descriptor_header const**) ; 

int usb_gadget_config_buf(
	const struct usb_config_descriptor	*config,
	void					*buf,
	unsigned				length,
	const struct usb_descriptor_header	**desc
)
{
	struct usb_config_descriptor		*cp = buf;
	int					len;

	/* config descriptor first */
	if (length < USB_DT_CONFIG_SIZE || !desc)
		return -EINVAL;
	*cp = *config;

	/* then interface/endpoint/class/vendor/... */
	len = usb_descriptor_fillbuf(USB_DT_CONFIG_SIZE + (u8*)buf,
			length - USB_DT_CONFIG_SIZE, desc);
	if (len < 0)
		return len;
	len += USB_DT_CONFIG_SIZE;
	if (len > 0xffff)
		return -EINVAL;

	/* patch up the config descriptor */
	cp->bLength = USB_DT_CONFIG_SIZE;
	cp->bDescriptorType = USB_DT_CONFIG;
	cp->wTotalLength = cpu_to_le16(len);
	cp->bmAttributes |= USB_CONFIG_ATT_ONE;
	return len;
}