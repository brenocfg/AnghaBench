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
struct usb_gadget {int dummy; } ;
struct usb_descriptor_header {int dummy; } ;
struct usb_config_descriptor {int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUFSIZ ; 
 int usb_gadget_config_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_descriptor_header const**) ; 
 int /*<<< orphan*/  z_config ; 
 struct usb_descriptor_header** z_function ; 

__attribute__((used)) static int
config_buf (struct usb_gadget *gadget, u8 *buf, u8 type, unsigned index)
{
	int len;
	const struct usb_descriptor_header **function;

	function = z_function;
	len = usb_gadget_config_buf (&z_config, buf, USB_BUFSIZ, function);
	if (len < 0)
		return len;
	((struct usb_config_descriptor *) buf)->bDescriptorType = type;
	return len;
}