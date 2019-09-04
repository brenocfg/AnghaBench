#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct TYPE_10__ {scalar_t__ prtspd; } ;
struct TYPE_11__ {TYPE_3__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_4__ hprt0_data_t ;
struct TYPE_12__ {TYPE_2__* core_if; } ;
typedef  TYPE_5__ dwc_otg_hcd_t ;
struct TYPE_9__ {TYPE_1__* host_if; } ;
struct TYPE_8__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 scalar_t__ DWC_HPRT0_PRTSPD_HIGH_SPEED ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ ) ; 
 int dwc_otg_hcd_get_frame_number (TYPE_5__*) ; 
 TYPE_5__* hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int get_frame_number(struct usb_hcd *hcd)
{
	hprt0_data_t hprt0;
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);
	hprt0.d32 = DWC_READ_REG32(dwc_otg_hcd->core_if->host_if->hprt0);
	if (hprt0.b.prtspd == DWC_HPRT0_PRTSPD_HIGH_SPEED)
		return dwc_otg_hcd_get_frame_number(dwc_otg_hcd) >> 3;
	else
		return dwc_otg_hcd_get_frame_number(dwc_otg_hcd);
}