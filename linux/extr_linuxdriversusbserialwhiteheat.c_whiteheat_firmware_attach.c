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
struct usb_serial {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int whiteheat_firmware_attach(struct usb_serial *serial)
{
	/* We want this device to fail to have a driver assigned to it */
	return 1;
}