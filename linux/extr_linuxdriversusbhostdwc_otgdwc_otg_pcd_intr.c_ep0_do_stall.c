#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_2__ usb_device_request_t ;
struct TYPE_13__ {int is_in; } ;
struct TYPE_12__ {int stopped; TYPE_7__ dwc_ep; } ;
struct TYPE_11__ {int /*<<< orphan*/  ep0state; TYPE_4__ ep0; TYPE_1__* setup_pkt; } ;
typedef  TYPE_3__ dwc_otg_pcd_t ;
typedef  TYPE_4__ dwc_otg_pcd_ep_t ;
struct TYPE_9__ {TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  EP0_IDLE ; 
 int /*<<< orphan*/  GET_CORE_IF (TYPE_3__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_set_stall (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ep0_out_start (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static inline void ep0_do_stall(dwc_otg_pcd_t * pcd, const int err_val)
{
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	usb_device_request_t *ctrl = &pcd->setup_pkt->req;
	DWC_WARN("req %02x.%02x protocol STALL; err %d\n",
		 ctrl->bmRequestType, ctrl->bRequest, err_val);

	ep0->dwc_ep.is_in = 1;
	dwc_otg_ep_set_stall(GET_CORE_IF(pcd), &ep0->dwc_ep);
	pcd->ep0.stopped = 1;
	pcd->ep0state = EP0_IDLE;
	ep0_out_start(GET_CORE_IF(pcd), pcd);
}