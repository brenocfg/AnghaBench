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
struct TYPE_11__ {scalar_t__ perschedena; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_4__ b; } ;
typedef  TYPE_5__ hcfg_data_t ;
struct TYPE_13__ {TYPE_3__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_10__ {TYPE_2__* host_if; } ;
struct TYPE_9__ {TYPE_1__* host_global_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  hcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void per_sched_disable(dwc_otg_hcd_t * hcd)
{
	hcfg_data_t hcfg;

	hcfg.d32 = DWC_READ_REG32(&hcd->core_if->host_if->host_global_regs->hcfg);

	if (!hcfg.b.perschedena) {
		/* already disabled */
		return;
	}
	hcfg.b.perschedena = 0;

	DWC_DEBUGPL(DBG_HCD, "Disabling Periodic schedule\n");
	DWC_WRITE_REG32(&hcd->core_if->host_if->host_global_regs->hcfg, hcfg.d32);
}