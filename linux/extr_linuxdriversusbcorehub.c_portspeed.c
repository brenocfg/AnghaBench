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
struct usb_hub {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 scalar_t__ hub_is_superspeed (int /*<<< orphan*/ ) ; 
 scalar_t__ hub_is_superspeedplus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *portspeed(struct usb_hub *hub, int portstatus)
{
	if (hub_is_superspeedplus(hub->hdev))
		return "10.0 Gb/s";
	if (hub_is_superspeed(hub->hdev))
		return "5.0 Gb/s";
	if (portstatus & USB_PORT_STAT_HIGH_SPEED)
		return "480 Mb/s";
	else if (portstatus & USB_PORT_STAT_LOW_SPEED)
		return "1.5 Mb/s";
	else
		return "12 Mb/s";
}