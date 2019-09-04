#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_global_regs_backup {int gotgctl_local; int gintmsk_local; int gusbcfg_local; int gahbcfg_local; int grxfsiz_local; int gnptxfsiz_local; int hptxfsiz_local; int gdfifocfg_local; int* dtxfsiz_local; } ;
struct TYPE_7__ {TYPE_2__* core_global_regs; TYPE_1__* host_if; struct dwc_otg_global_regs_backup* gr_backup; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_6__ {int /*<<< orphan*/  gahbcfg; int /*<<< orphan*/  gintsts; int /*<<< orphan*/ * dtxfsiz; int /*<<< orphan*/  gdfifocfg; int /*<<< orphan*/  hptxfsiz; int /*<<< orphan*/  gnptxfsiz; int /*<<< orphan*/  grxfsiz; int /*<<< orphan*/  gusbcfg; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gotgctl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hprt0; } ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int MAX_EPS_CHANNELS ; 

int dwc_otg_restore_global_regs(dwc_otg_core_if_t *core_if)
{
	struct dwc_otg_global_regs_backup *gr;
	int i;

	gr = core_if->gr_backup;
	if (!gr) {
		return -DWC_E_INVALID;
	}

	DWC_WRITE_REG32(&core_if->core_global_regs->gotgctl, gr->gotgctl_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->gintmsk, gr->gintmsk_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->gusbcfg, gr->gusbcfg_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->gahbcfg, gr->gahbcfg_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->grxfsiz, gr->grxfsiz_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->gnptxfsiz,
			gr->gnptxfsiz_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->hptxfsiz,
			gr->hptxfsiz_local);
	DWC_WRITE_REG32(&core_if->core_global_regs->gdfifocfg,
			gr->gdfifocfg_local);
	for (i = 0; i < MAX_EPS_CHANNELS; i++) {
		DWC_WRITE_REG32(&core_if->core_global_regs->dtxfsiz[i],
				gr->dtxfsiz_local[i]);
	}

	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, 0xFFFFFFFF);
	DWC_WRITE_REG32(core_if->host_if->hprt0, 0x0000100A);
	DWC_WRITE_REG32(&core_if->core_global_regs->gahbcfg,
			(gr->gahbcfg_local));
	return 0;
}