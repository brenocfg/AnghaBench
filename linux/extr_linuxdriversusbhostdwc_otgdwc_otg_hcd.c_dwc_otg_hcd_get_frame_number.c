#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int frnum; } ;
struct TYPE_12__ {TYPE_4__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_5__ hfnum_data_t ;
struct TYPE_13__ {TYPE_3__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_10__ {TYPE_2__* host_if; } ;
struct TYPE_9__ {TYPE_1__* host_global_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  hfnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

int dwc_otg_hcd_get_frame_number(dwc_otg_hcd_t * dwc_otg_hcd)
{
	hfnum_data_t hfnum;
	hfnum.d32 =
	    DWC_READ_REG32(&dwc_otg_hcd->core_if->host_if->host_global_regs->
			   hfnum);

#ifdef DEBUG_SOF
	DWC_DEBUGPL(DBG_HCDV, "DWC OTG HCD GET FRAME NUMBER %d\n",
		    hfnum.b.frnum);
#endif
	return hfnum.b.frnum;
}