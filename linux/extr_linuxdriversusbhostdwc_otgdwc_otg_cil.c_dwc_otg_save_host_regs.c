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
struct dwc_otg_host_regs_backup {void* hfir_local; void* hprt0_local; void** hcintmsk_local; void* haintmsk_local; void* hcfg_local; } ;
struct TYPE_10__ {TYPE_3__* host_if; struct dwc_otg_host_regs_backup* hr_backup; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {TYPE_2__* host_global_regs; int /*<<< orphan*/ * hprt0; TYPE_1__** hc_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  hfir; int /*<<< orphan*/  haintmsk; int /*<<< orphan*/  hcfg; } ;
struct TYPE_7__ {int /*<<< orphan*/  hcintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 struct dwc_otg_host_regs_backup* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int DWC_E_NO_MEMORY ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int dwc_otg_get_param_host_channels (TYPE_4__*) ; 

int dwc_otg_save_host_regs(dwc_otg_core_if_t * core_if)
{
	struct dwc_otg_host_regs_backup *hr;
	int i;

	hr = core_if->hr_backup;
	if (!hr) {
		hr = DWC_ALLOC(sizeof(*hr));
		if (!hr) {
			return -DWC_E_NO_MEMORY;
		}
		core_if->hr_backup = hr;
	}

	hr->hcfg_local =
	    DWC_READ_REG32(&core_if->host_if->host_global_regs->hcfg);
	hr->haintmsk_local =
	    DWC_READ_REG32(&core_if->host_if->host_global_regs->haintmsk);
	for (i = 0; i < dwc_otg_get_param_host_channels(core_if); ++i) {
		hr->hcintmsk_local[i] =
		    DWC_READ_REG32(&core_if->host_if->hc_regs[i]->hcintmsk);
	}
	hr->hprt0_local = DWC_READ_REG32(core_if->host_if->hprt0);
	hr->hfir_local =
	    DWC_READ_REG32(&core_if->host_if->host_global_regs->hfir);

	DWC_DEBUGPL(DBG_ANY,
		    "=============Backing Host registers===============\n");
	DWC_DEBUGPL(DBG_ANY, "Backed up hcfg		= %08x\n",
		    hr->hcfg_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up haintmsk = %08x\n", hr->haintmsk_local);
	for (i = 0; i < dwc_otg_get_param_host_channels(core_if); ++i) {
		DWC_DEBUGPL(DBG_ANY, "Backed up hcintmsk[%02d]=%08x\n", i,
			    hr->hcintmsk_local[i]);
	}
	DWC_DEBUGPL(DBG_ANY, "Backed up hprt0           = %08x\n",
		    hr->hprt0_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up hfir           = %08x\n",
		    hr->hfir_local);

	return 0;
}