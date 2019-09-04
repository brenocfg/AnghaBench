#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_device_request_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int request_config; int /*<<< orphan*/  lock; TYPE_1__* fops; } ;
typedef  TYPE_2__ dwc_otg_pcd_t ;
struct TYPE_6__ {int (* setup ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_do_stall (TYPE_2__*,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void do_gadget_setup(dwc_otg_pcd_t * pcd,
				   usb_device_request_t * ctrl)
{
	int ret = 0;
	DWC_SPINUNLOCK(pcd->lock);
	ret = pcd->fops->setup(pcd, (uint8_t *) ctrl);
	DWC_SPINLOCK(pcd->lock);
	if (ret < 0) {
		ep0_do_stall(pcd, ret);
	}

	/** @todo This is a g_file_storage gadget driver specific
	 * workaround: a DELAYED_STATUS result from the fsg_setup
	 * routine will result in the gadget queueing a EP0 IN status
	 * phase for a two-stage control transfer. Exactly the same as
	 * a SET_CONFIGURATION/SET_INTERFACE except that this is a class
	 * specific request.  Need a generic way to know when the gadget
	 * driver will queue the status phase. Can we assume when we
	 * call the gadget driver setup() function that it will always
	 * queue and require the following flag? Need to look into
	 * this.
	 */

	if (ret == 256 + 999) {
		pcd->request_config = 1;
	}
}