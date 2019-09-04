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
typedef  int /*<<< orphan*/  u16 ;
struct usb_hub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_PORT_STATUS ; 
 int hub_ext_port_status (struct usb_hub*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hub_port_status(struct usb_hub *hub, int port1,
		u16 *status, u16 *change)
{
	return hub_ext_port_status(hub, port1, HUB_PORT_STATUS,
				   status, change, NULL);
}