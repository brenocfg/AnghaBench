#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  maxpacket; } ;
struct TYPE_15__ {TYPE_3__ dwc_ep; int /*<<< orphan*/  queue; } ;
struct TYPE_14__ {TYPE_5__ ep0; int /*<<< orphan*/  ep0state; TYPE_5__* out_ep; TYPE_5__* in_ep; } ;
typedef  TYPE_4__ dwc_otg_pcd_t ;
typedef  TYPE_5__ dwc_otg_pcd_ep_t ;
struct TYPE_12__ {int d32; } ;
struct TYPE_16__ {TYPE_2__ hwcfg1; TYPE_1__* dev_if; } ;
struct TYPE_11__ {int num_in_eps; int num_out_eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_OTG_EP_TYPE_CONTROL ; 
 int /*<<< orphan*/  EP0_DISCONNECT ; 
 TYPE_9__* GET_CORE_IF (TYPE_4__*) ; 
 int /*<<< orphan*/  MAX_EP0_SIZE ; 
 int /*<<< orphan*/  dwc_otg_pcd_init_ep (TYPE_4__*,TYPE_5__*,int,int) ; 

__attribute__((used)) static void dwc_otg_pcd_reinit(dwc_otg_pcd_t * pcd)
{
	int i;
	uint32_t hwcfg1;
	dwc_otg_pcd_ep_t *ep;
	int in_ep_cntr, out_ep_cntr;
	uint32_t num_in_eps = (GET_CORE_IF(pcd))->dev_if->num_in_eps;
	uint32_t num_out_eps = (GET_CORE_IF(pcd))->dev_if->num_out_eps;

	/**
	 * Initialize the EP0 structure.
	 */
	ep = &pcd->ep0;
	dwc_otg_pcd_init_ep(pcd, ep, 0, 0);

	in_ep_cntr = 0;
	hwcfg1 = (GET_CORE_IF(pcd))->hwcfg1.d32 >> 3;
	for (i = 1; in_ep_cntr < num_in_eps; i++) {
		if ((hwcfg1 & 0x1) == 0) {
			dwc_otg_pcd_ep_t *ep = &pcd->in_ep[in_ep_cntr];
			in_ep_cntr++;
			/**
			 * @todo NGS: Add direction to EP, based on contents
			 * of HWCFG1.  Need a copy of HWCFG1 in pcd structure?
			 * sprintf(";r
			 */
			dwc_otg_pcd_init_ep(pcd, ep, 1 /* IN */ , i);

			DWC_CIRCLEQ_INIT(&ep->queue);
		}
		hwcfg1 >>= 2;
	}

	out_ep_cntr = 0;
	hwcfg1 = (GET_CORE_IF(pcd))->hwcfg1.d32 >> 2;
	for (i = 1; out_ep_cntr < num_out_eps; i++) {
		if ((hwcfg1 & 0x1) == 0) {
			dwc_otg_pcd_ep_t *ep = &pcd->out_ep[out_ep_cntr];
			out_ep_cntr++;
			/**
			 * @todo NGS: Add direction to EP, based on contents
			 * of HWCFG1.  Need a copy of HWCFG1 in pcd structure?
			 * sprintf(";r
			 */
			dwc_otg_pcd_init_ep(pcd, ep, 0 /* OUT */ , i);
			DWC_CIRCLEQ_INIT(&ep->queue);
		}
		hwcfg1 >>= 2;
	}

	pcd->ep0state = EP0_DISCONNECT;
	pcd->ep0.dwc_ep.maxpacket = MAX_EP0_SIZE;
	pcd->ep0.dwc_ep.type = DWC_OTG_EP_TYPE_CONTROL;
}