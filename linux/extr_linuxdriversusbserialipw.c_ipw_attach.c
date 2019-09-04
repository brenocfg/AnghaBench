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
struct usb_wwan_intf_private {int /*<<< orphan*/  susp_lock; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb_wwan_intf_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,struct usb_wwan_intf_private*) ; 

__attribute__((used)) static int ipw_attach(struct usb_serial *serial)
{
	struct usb_wwan_intf_private *data;

	data = kzalloc(sizeof(struct usb_wwan_intf_private), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	spin_lock_init(&data->susp_lock);
	usb_set_serial_data(serial, data);
	return 0;
}