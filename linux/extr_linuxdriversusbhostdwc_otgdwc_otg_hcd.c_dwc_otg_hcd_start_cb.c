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
typedef  int int32_t ;
struct TYPE_8__ {int prtrst; } ;
struct TYPE_10__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_11__ {TYPE_5__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
struct TYPE_12__ {scalar_t__ op_state; int /*<<< orphan*/  wq_otg; TYPE_2__* host_if; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 scalar_t__ B_HOST ; 
 int /*<<< orphan*/  DWC_WORKQ_SCHEDULE_DELAYED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_read_hprt0 (TYPE_5__*) ; 
 int /*<<< orphan*/  hcd_start_func ; 

__attribute__((used)) static int32_t dwc_otg_hcd_start_cb(void *p)
{
	dwc_otg_hcd_t *dwc_otg_hcd = p;
	dwc_otg_core_if_t *core_if;
	hprt0_data_t hprt0;

	core_if = dwc_otg_hcd->core_if;

	if (core_if->op_state == B_HOST) {
		/*
		 * Reset the port.  During a HNP mode switch the reset
		 * needs to occur within 1ms and have a duration of at
		 * least 50ms.
		 */
		hprt0.d32 = dwc_otg_read_hprt0(core_if);
		hprt0.b.prtrst = 1;
		DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
	}
	DWC_WORKQ_SCHEDULE_DELAYED(core_if->wq_otg,
				   hcd_start_func, dwc_otg_hcd, 50,
				   "start hcd");

	return 1;
}