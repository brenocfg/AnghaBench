#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_ctrlrequest {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_4__ {int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_3__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 int DWC_E_NOT_SUPPORTED ; 
 int ENOTSUPP ; 
 TYPE_2__* gadget_wrapper ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static int _setup(dwc_otg_pcd_t * pcd, uint8_t * bytes)
{
	int retval = -DWC_E_NOT_SUPPORTED;
	if (gadget_wrapper->driver && gadget_wrapper->driver->setup) {
		retval = gadget_wrapper->driver->setup(&gadget_wrapper->gadget,
						       (struct usb_ctrlrequest
							*)bytes);
	}

	if (retval == -ENOTSUPP) {
		retval = -DWC_E_NOT_SUPPORTED;
	} else if (retval < 0) {
		retval = -DWC_E_INVALID;
	}

	return retval;
}