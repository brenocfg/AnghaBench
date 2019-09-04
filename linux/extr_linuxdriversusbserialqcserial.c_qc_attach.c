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
struct usb_wwan_intf_private {int use_send_setup; int /*<<< orphan*/  susp_lock; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb_wwan_intf_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,struct usb_wwan_intf_private*) ; 

__attribute__((used)) static int qc_attach(struct usb_serial *serial)
{
	struct usb_wwan_intf_private *data;
	bool sendsetup;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	sendsetup = !!(unsigned long)(usb_get_serial_data(serial));
	if (sendsetup)
		data->use_send_setup = 1;

	spin_lock_init(&data->susp_lock);

	usb_set_serial_data(serial, data);

	return 0;
}