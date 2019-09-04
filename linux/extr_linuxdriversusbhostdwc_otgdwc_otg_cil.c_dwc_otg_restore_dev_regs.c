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
struct dwc_otg_dev_regs_backup {int /*<<< orphan*/ * diepctl; int /*<<< orphan*/ * diepdma; int /*<<< orphan*/ * dieptsiz; int /*<<< orphan*/  doepmsk; int /*<<< orphan*/  diepmsk; int /*<<< orphan*/  daintmsk; int /*<<< orphan*/  dctl; } ;
struct TYPE_9__ {TYPE_3__* dev_if; struct dwc_otg_dev_regs_backup* dr_backup; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int num_in_eps; TYPE_2__** in_ep_regs; TYPE_1__* dev_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  diepctl; int /*<<< orphan*/  diepdma; int /*<<< orphan*/  dieptsiz; } ;
struct TYPE_6__ {int /*<<< orphan*/  doepmsk; int /*<<< orphan*/  diepmsk; int /*<<< orphan*/  daintmsk; int /*<<< orphan*/  dctl; } ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dwc_otg_restore_dev_regs(dwc_otg_core_if_t * core_if, int rem_wakeup)
{
	struct dwc_otg_dev_regs_backup *dr;
	int i;

	dr = core_if->dr_backup;

	if (!dr) {
		return -DWC_E_INVALID;
	}

	if (!rem_wakeup) {
		DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dctl,
				dr->dctl);
	}

	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->daintmsk, dr->daintmsk);
	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->diepmsk, dr->diepmsk);
	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->doepmsk, dr->doepmsk);

	for (i = 0; i < core_if->dev_if->num_in_eps; ++i) {
		DWC_WRITE_REG32(&core_if->dev_if->in_ep_regs[i]->dieptsiz, dr->dieptsiz[i]);
		DWC_WRITE_REG32(&core_if->dev_if->in_ep_regs[i]->diepdma, dr->diepdma[i]);
		DWC_WRITE_REG32(&core_if->dev_if->in_ep_regs[i]->diepctl, dr->diepctl[i]);
	}

	return 0;
}