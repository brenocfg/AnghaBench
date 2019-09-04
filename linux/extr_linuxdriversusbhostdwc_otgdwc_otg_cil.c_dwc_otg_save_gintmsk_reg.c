#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_global_regs_backup {int /*<<< orphan*/  gintmsk_local; } ;
struct TYPE_5__ {TYPE_1__* core_global_regs; struct dwc_otg_global_regs_backup* gr_backup; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 struct dwc_otg_global_regs_backup* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int DWC_E_NO_MEMORY ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

int dwc_otg_save_gintmsk_reg(dwc_otg_core_if_t * core_if)
{
	struct dwc_otg_global_regs_backup *gr;

	gr = core_if->gr_backup;
	if (!gr) {
		gr = DWC_ALLOC(sizeof(*gr));
		if (!gr) {
			return -DWC_E_NO_MEMORY;
		}
		core_if->gr_backup = gr;
	}

	gr->gintmsk_local = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);

	DWC_DEBUGPL(DBG_ANY,"=============Backing GINTMSK registers============\n");
	DWC_DEBUGPL(DBG_ANY, "Backed up gintmsk   = %08x\n", gr->gintmsk_local);

	return 0;
}