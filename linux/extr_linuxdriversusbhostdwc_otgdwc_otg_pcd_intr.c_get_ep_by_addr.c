#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * out_ep; int /*<<< orphan*/ * in_ep; int /*<<< orphan*/  ep0; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_ep_t ;

/* Variables and functions */
 scalar_t__ UE_DIR_IN ; 
 int UE_GET_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_GET_DIR (int /*<<< orphan*/ ) ; 

dwc_otg_pcd_ep_t *get_ep_by_addr(dwc_otg_pcd_t * pcd, u16 wIndex)
{
	dwc_otg_pcd_ep_t *ep;
	uint32_t ep_num = UE_GET_ADDR(wIndex);

	if (ep_num == 0) {
		ep = &pcd->ep0;
	} else if (UE_GET_DIR(wIndex) == UE_DIR_IN) {	/* in ep */
		ep = &pcd->in_ep[ep_num - 1];
	} else {
		ep = &pcd->out_ep[ep_num - 1];
	}

	return ep;
}