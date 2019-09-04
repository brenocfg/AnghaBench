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
struct usb_hub {int dummy; } ;

/* Variables and functions */
 int hub_port_debounce (struct usb_hub*,int,int) ; 

__attribute__((used)) static inline int hub_port_debounce_be_connected(struct usb_hub *hub,
		int port1)
{
	return hub_port_debounce(hub, port1, true);
}