#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_host_regs_backup {int /*<<< orphan*/ * hcintmsk_local; int /*<<< orphan*/  haintmsk_local; int /*<<< orphan*/  hcfg_local; } ;
struct TYPE_10__ {TYPE_2__* host_if; struct dwc_otg_host_regs_backup* hr_backup; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  haintmsk; int /*<<< orphan*/  hcfg; } ;
struct TYPE_8__ {TYPE_1__** hc_regs; TYPE_3__* host_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  hcintmsk; } ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_get_param_host_channels (TYPE_4__*) ; 

int dwc_otg_restore_host_regs(dwc_otg_core_if_t * core_if, int reset)
{
	struct dwc_otg_host_regs_backup *hr;
	int i;
	hr = core_if->hr_backup;

	if (!hr) {
		return -DWC_E_INVALID;
	}

	DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hcfg, hr->hcfg_local);
	//if (!reset)
	//{
	//      DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hfir, hr->hfir_local);
	//}

	DWC_WRITE_REG32(&core_if->host_if->host_global_regs->haintmsk,
			hr->haintmsk_local);
	for (i = 0; i < dwc_otg_get_param_host_channels(core_if); ++i) {
		DWC_WRITE_REG32(&core_if->host_if->hc_regs[i]->hcintmsk,
				hr->hcintmsk_local[i]);
	}

	return 0;
}