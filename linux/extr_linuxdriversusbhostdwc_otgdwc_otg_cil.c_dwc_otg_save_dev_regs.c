#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_dev_regs_backup {void** diepdma; void** dieptsiz; void** diepctl; void* doepmsk; void* diepmsk; void* daintmsk; void* dctl; void* dcfg; } ;
struct TYPE_9__ {TYPE_3__* dev_if; struct dwc_otg_dev_regs_backup* dr_backup; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int num_in_eps; TYPE_2__** in_ep_regs; TYPE_1__* dev_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  diepdma; int /*<<< orphan*/  dieptsiz; int /*<<< orphan*/  diepctl; } ;
struct TYPE_6__ {int /*<<< orphan*/  doepmsk; int /*<<< orphan*/  diepmsk; int /*<<< orphan*/  daintmsk; int /*<<< orphan*/  dctl; int /*<<< orphan*/  dcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 struct dwc_otg_dev_regs_backup* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int DWC_E_NO_MEMORY ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

int dwc_otg_save_dev_regs(dwc_otg_core_if_t * core_if)
{
	struct dwc_otg_dev_regs_backup *dr;
	int i;

	dr = core_if->dr_backup;
	if (!dr) {
		dr = DWC_ALLOC(sizeof(*dr));
		if (!dr) {
			return -DWC_E_NO_MEMORY;
		}
		core_if->dr_backup = dr;
	}

	dr->dcfg = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dcfg);
	dr->dctl = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dctl);
	dr->daintmsk =
	    DWC_READ_REG32(&core_if->dev_if->dev_global_regs->daintmsk);
	dr->diepmsk =
	    DWC_READ_REG32(&core_if->dev_if->dev_global_regs->diepmsk);
	dr->doepmsk =
	    DWC_READ_REG32(&core_if->dev_if->dev_global_regs->doepmsk);

	for (i = 0; i < core_if->dev_if->num_in_eps; ++i) {
		dr->diepctl[i] =
		    DWC_READ_REG32(&core_if->dev_if->in_ep_regs[i]->diepctl);
		dr->dieptsiz[i] =
		    DWC_READ_REG32(&core_if->dev_if->in_ep_regs[i]->dieptsiz);
		dr->diepdma[i] =
		    DWC_READ_REG32(&core_if->dev_if->in_ep_regs[i]->diepdma);
	}

	DWC_DEBUGPL(DBG_ANY,
		    "=============Backing Host registers==============\n");
	DWC_DEBUGPL(DBG_ANY, "Backed up dcfg            = %08x\n", dr->dcfg);
	DWC_DEBUGPL(DBG_ANY, "Backed up dctl        = %08x\n", dr->dctl);
	DWC_DEBUGPL(DBG_ANY, "Backed up daintmsk            = %08x\n",
		    dr->daintmsk);
	DWC_DEBUGPL(DBG_ANY, "Backed up diepmsk        = %08x\n", dr->diepmsk);
	DWC_DEBUGPL(DBG_ANY, "Backed up doepmsk        = %08x\n", dr->doepmsk);
	for (i = 0; i < core_if->dev_if->num_in_eps; ++i) {
		DWC_DEBUGPL(DBG_ANY, "Backed up diepctl[%d]        = %08x\n", i,
			    dr->diepctl[i]);
		DWC_DEBUGPL(DBG_ANY, "Backed up dieptsiz[%d]        = %08x\n",
			    i, dr->dieptsiz[i]);
		DWC_DEBUGPL(DBG_ANY, "Backed up diepdma[%d]        = %08x\n", i,
			    dr->diepdma[i]);
	}

	return 0;
}