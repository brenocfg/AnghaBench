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
struct dwc_otg_global_regs_backup {int /*<<< orphan*/  gi2cctl_local; } ;
struct TYPE_5__ {TYPE_1__* core_global_regs; struct dwc_otg_global_regs_backup* gr_backup; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/  gi2cctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int restore_lpm_i2c_regs(dwc_otg_core_if_t * core_if)
{
	struct dwc_otg_global_regs_backup *gr;

	gr = core_if->gr_backup;

	/* Restore values for LPM and I2C */
#ifdef CONFIG_USB_DWC_OTG_LPM
	DWC_WRITE_REG32(&core_if->core_global_regs->glpmcfg, gr->glpmcfg_local);
#endif
	DWC_WRITE_REG32(&core_if->core_global_regs->gi2cctl, gr->gi2cctl_local);

	return 0;
}