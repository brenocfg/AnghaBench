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
typedef  int u32 ;

/* Variables and functions */
 int PORT_PLS_MASK ; 
 int USB_PORT_STAT_L1 ; 
 int XDEV_U2 ; 

__attribute__((used)) static void xhci_hub_report_usb2_link_state(u32 *status, u32 status_reg)
{
	if ((status_reg & PORT_PLS_MASK) == XDEV_U2)
		*status |= USB_PORT_STAT_L1;
}