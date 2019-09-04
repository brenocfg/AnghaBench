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
struct dwc_otg_global_regs_backup {void* gdfifocfg_local; void* pcgcctl_local; void* gi2cctl_local; void* hptxfsiz_local; void* gnptxfsiz_local; void* grxfsiz_local; void* gusbcfg_local; void* gahbcfg_local; void* gintmsk_local; void* gotgctl_local; void** dtxfsiz_local; } ;
struct TYPE_5__ {TYPE_1__* core_global_regs; int /*<<< orphan*/ * pcgcctl; struct dwc_otg_global_regs_backup* gr_backup; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dtxfsiz; int /*<<< orphan*/  gdfifocfg; int /*<<< orphan*/  gi2cctl; int /*<<< orphan*/  hptxfsiz; int /*<<< orphan*/  gnptxfsiz; int /*<<< orphan*/  grxfsiz; int /*<<< orphan*/  gusbcfg; int /*<<< orphan*/  gahbcfg; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 struct dwc_otg_global_regs_backup* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int DWC_E_NO_MEMORY ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int MAX_EPS_CHANNELS ; 

int dwc_otg_save_global_regs(dwc_otg_core_if_t * core_if)
{
	struct dwc_otg_global_regs_backup *gr;
	int i;

	gr = core_if->gr_backup;
	if (!gr) {
		gr = DWC_ALLOC(sizeof(*gr));
		if (!gr) {
			return -DWC_E_NO_MEMORY;
		}
		core_if->gr_backup = gr;
	}

	gr->gotgctl_local = DWC_READ_REG32(&core_if->core_global_regs->gotgctl);
	gr->gintmsk_local = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);
	gr->gahbcfg_local = DWC_READ_REG32(&core_if->core_global_regs->gahbcfg);
	gr->gusbcfg_local = DWC_READ_REG32(&core_if->core_global_regs->gusbcfg);
	gr->grxfsiz_local = DWC_READ_REG32(&core_if->core_global_regs->grxfsiz);
	gr->gnptxfsiz_local = DWC_READ_REG32(&core_if->core_global_regs->gnptxfsiz);
	gr->hptxfsiz_local = DWC_READ_REG32(&core_if->core_global_regs->hptxfsiz);
#ifdef CONFIG_USB_DWC_OTG_LPM
	gr->glpmcfg_local = DWC_READ_REG32(&core_if->core_global_regs->glpmcfg);
#endif
	gr->gi2cctl_local = DWC_READ_REG32(&core_if->core_global_regs->gi2cctl);
	gr->pcgcctl_local = DWC_READ_REG32(core_if->pcgcctl);
	gr->gdfifocfg_local =
	    DWC_READ_REG32(&core_if->core_global_regs->gdfifocfg);
	for (i = 0; i < MAX_EPS_CHANNELS; i++) {
		gr->dtxfsiz_local[i] =
		    DWC_READ_REG32(&(core_if->core_global_regs->dtxfsiz[i]));
	}

	DWC_DEBUGPL(DBG_ANY, "===========Backing Global registers==========\n");
	DWC_DEBUGPL(DBG_ANY, "Backed up gotgctl   = %08x\n", gr->gotgctl_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up gintmsk   = %08x\n", gr->gintmsk_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up gahbcfg   = %08x\n", gr->gahbcfg_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up gusbcfg   = %08x\n", gr->gusbcfg_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up grxfsiz   = %08x\n", gr->grxfsiz_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up gnptxfsiz = %08x\n",
		    gr->gnptxfsiz_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up hptxfsiz  = %08x\n",
		    gr->hptxfsiz_local);
#ifdef CONFIG_USB_DWC_OTG_LPM
	DWC_DEBUGPL(DBG_ANY, "Backed up glpmcfg   = %08x\n", gr->glpmcfg_local);
#endif
	DWC_DEBUGPL(DBG_ANY, "Backed up gi2cctl   = %08x\n", gr->gi2cctl_local);
	DWC_DEBUGPL(DBG_ANY, "Backed up pcgcctl   = %08x\n", gr->pcgcctl_local);
	DWC_DEBUGPL(DBG_ANY,"Backed up gdfifocfg   = %08x\n",gr->gdfifocfg_local);

	return 0;
}