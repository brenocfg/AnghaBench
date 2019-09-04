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
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYSDEVOP_DBGP_RESET_PREPARE ; 
 int xen_dbgp_op (struct usb_hcd*,int /*<<< orphan*/ ) ; 

int xen_dbgp_reset_prep(struct usb_hcd *hcd)
{
	return xen_dbgp_op(hcd, PHYSDEVOP_DBGP_RESET_PREPARE);
}