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
typedef  int uint16_t ;
struct TYPE_8__ {int perschedena; int frlisten; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_5__ hcfg_data_t ;
struct TYPE_13__ {TYPE_4__* core_if; int /*<<< orphan*/  frame_list_dma; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_11__ {TYPE_3__* host_if; } ;
struct TYPE_10__ {TYPE_2__* host_global_regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  hcfg; int /*<<< orphan*/  hflbaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void per_sched_enable(dwc_otg_hcd_t * hcd, uint16_t fr_list_en)
{

	hcfg_data_t hcfg;

	hcfg.d32 = DWC_READ_REG32(&hcd->core_if->host_if->host_global_regs->hcfg);

	if (hcfg.b.perschedena) {
		/* already enabled */
		return;
	}

	DWC_WRITE_REG32(&hcd->core_if->host_if->host_global_regs->hflbaddr,
			hcd->frame_list_dma);

	switch (fr_list_en) {
	case 64:
		hcfg.b.frlisten = 3;
		break;
	case 32:
		hcfg.b.frlisten = 2;
		break;
	case 16:
		hcfg.b.frlisten = 1;
		break;
	case 8:
		hcfg.b.frlisten = 0;
		break;
	default:
		break;
	}

	hcfg.b.perschedena = 1;

	DWC_DEBUGPL(DBG_HCD, "Enabling Periodic schedule\n");
	DWC_WRITE_REG32(&hcd->core_if->host_if->host_global_regs->hcfg, hcfg.d32);

}