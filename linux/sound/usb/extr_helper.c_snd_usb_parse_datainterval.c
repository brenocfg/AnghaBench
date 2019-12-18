#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_host_interface {int dummy; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int bInterval; } ;

/* Variables and functions */
#define  USB_SPEED_HIGH 131 
#define  USB_SPEED_SUPER 130 
#define  USB_SPEED_SUPER_PLUS 129 
#define  USB_SPEED_WIRELESS 128 
 TYPE_1__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 int snd_usb_get_speed (int /*<<< orphan*/ ) ; 

unsigned char snd_usb_parse_datainterval(struct snd_usb_audio *chip,
					 struct usb_host_interface *alts)
{
	switch (snd_usb_get_speed(chip->dev)) {
	case USB_SPEED_HIGH:
	case USB_SPEED_WIRELESS:
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
		if (get_endpoint(alts, 0)->bInterval >= 1 &&
		    get_endpoint(alts, 0)->bInterval <= 4)
			return get_endpoint(alts, 0)->bInterval - 1;
		break;
	default:
		break;
	}
	return 0;
}