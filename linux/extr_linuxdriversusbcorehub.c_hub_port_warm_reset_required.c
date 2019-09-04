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
typedef  int u16 ;
struct usb_hub {int /*<<< orphan*/  warm_reset_bits; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int USB_PORT_STAT_LINK_STATE ; 
 int USB_SS_PORT_LS_COMP_MOD ; 
 int USB_SS_PORT_LS_SS_INACTIVE ; 
 int /*<<< orphan*/  hub_is_superspeed (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hub_port_warm_reset_required(struct usb_hub *hub, int port1,
		u16 portstatus)
{
	u16 link_state;

	if (!hub_is_superspeed(hub->hdev))
		return false;

	if (test_bit(port1, hub->warm_reset_bits))
		return true;

	link_state = portstatus & USB_PORT_STAT_LINK_STATE;
	return link_state == USB_SS_PORT_LS_SS_INACTIVE
		|| link_state == USB_SS_PORT_LS_COMP_MOD;
}