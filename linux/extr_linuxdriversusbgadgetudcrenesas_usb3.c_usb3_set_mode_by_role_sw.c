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
struct renesas_usb3 {int /*<<< orphan*/  role_work; int /*<<< orphan*/  role; scalar_t__ role_sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ROLE_DEVICE ; 
 int /*<<< orphan*/  USB_ROLE_HOST ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb3_set_mode (struct renesas_usb3*,int) ; 

__attribute__((used)) static void usb3_set_mode_by_role_sw(struct renesas_usb3 *usb3, bool host)
{
	if (usb3->role_sw) {
		usb3->role = host ? USB_ROLE_HOST : USB_ROLE_DEVICE;
		schedule_work(&usb3->role_work);
	} else {
		usb3_set_mode(usb3, host);
	}
}