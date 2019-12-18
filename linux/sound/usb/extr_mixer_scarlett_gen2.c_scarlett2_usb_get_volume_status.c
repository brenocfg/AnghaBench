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
struct usb_mixer_interface {int dummy; } ;
struct scarlett2_usb_volume_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_USB_VOLUME_STATUS_OFFSET ; 
 int scarlett2_usb_get (struct usb_mixer_interface*,int /*<<< orphan*/ ,struct scarlett2_usb_volume_status*,int) ; 

__attribute__((used)) static int scarlett2_usb_get_volume_status(
	struct usb_mixer_interface *mixer,
	struct scarlett2_usb_volume_status *buf)
{
	return scarlett2_usb_get(mixer, SCARLETT2_USB_VOLUME_STATUS_OFFSET,
				 buf, sizeof(*buf));
}