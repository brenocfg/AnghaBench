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
struct usb_ep {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int DWC_E_AGAIN ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int dwc_otg_pcd_ep_halt (int /*<<< orphan*/ ,struct usb_ep*,int) ; 
 TYPE_1__* gadget_wrapper ; 

__attribute__((used)) static int ep_halt(struct usb_ep *usb_ep, int value)
{
	int retval = 0;

	DWC_DEBUGPL(DBG_PCD, "HALT %s %d\n", usb_ep->name, value);

	if (!usb_ep) {
		DWC_WARN("bad ep\n");
		return -EINVAL;
	}

	retval = dwc_otg_pcd_ep_halt(gadget_wrapper->pcd, usb_ep, value);
	if (retval == -DWC_E_AGAIN) {
		return -EAGAIN;
	} else if (retval) {
		retval = -EINVAL;
	}

	return retval;
}