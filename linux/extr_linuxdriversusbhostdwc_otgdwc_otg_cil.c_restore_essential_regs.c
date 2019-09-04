#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct dwc_otg_global_regs_backup {int pcgcctl_local; int gahbcfg_local; int gusbcfg_local; } ;
struct TYPE_20__ {int restoremode; int ess_reg_restored; } ;
struct TYPE_21__ {int d32; TYPE_10__ b; } ;
typedef  TYPE_11__ pcgcctl_data_t ;
struct TYPE_22__ {int d32; } ;
typedef  TYPE_12__ hcfg_data_t ;
struct TYPE_23__ {int d32; } ;
typedef  TYPE_13__ gusbcfg_data_t ;
struct TYPE_29__ {int restoredone; } ;
struct TYPE_24__ {int d32; TYPE_2__ b; } ;
typedef  TYPE_14__ gintmsk_data_t ;
struct TYPE_28__ {int glblintrmsk; } ;
struct TYPE_25__ {int d32; TYPE_1__ b; } ;
typedef  TYPE_15__ gahbcfg_data_t ;
struct TYPE_26__ {int /*<<< orphan*/ * pcgcctl; TYPE_9__* dev_if; TYPE_7__* dr_backup; TYPE_6__* host_if; TYPE_4__* hr_backup; TYPE_3__* core_global_regs; struct dwc_otg_global_regs_backup* gr_backup; } ;
typedef  TYPE_16__ dwc_otg_core_if_t ;
struct TYPE_27__ {int d32; } ;
typedef  TYPE_17__ dcfg_data_t ;
struct TYPE_36__ {TYPE_8__* dev_global_regs; } ;
struct TYPE_35__ {int /*<<< orphan*/  dcfg; } ;
struct TYPE_34__ {int dcfg; } ;
struct TYPE_33__ {TYPE_5__* host_global_regs; } ;
struct TYPE_32__ {int /*<<< orphan*/  hcfg; } ;
struct TYPE_31__ {int hcfg_local; } ;
struct TYPE_30__ {int /*<<< orphan*/  gusbcfg; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gahbcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dwc_udelay (int) ; 
 int /*<<< orphan*/  restore_lpm_i2c_regs (TYPE_16__*) ; 

int restore_essential_regs(dwc_otg_core_if_t * core_if, int rmode, int is_host)
{
	struct dwc_otg_global_regs_backup *gr;
	pcgcctl_data_t pcgcctl = {.d32 = 0 };
	gahbcfg_data_t gahbcfg = {.d32 = 0 };
	gusbcfg_data_t gusbcfg = {.d32 = 0 };
	gintmsk_data_t gintmsk = {.d32 = 0 };

	/* Restore LPM and I2C registers */
	restore_lpm_i2c_regs(core_if);

	/* Set PCGCCTL to 0 */
	DWC_WRITE_REG32(core_if->pcgcctl, 0x00000000);

	gr = core_if->gr_backup;
	/* Load restore values for [31:14] bits */
	DWC_WRITE_REG32(core_if->pcgcctl,
			((gr->pcgcctl_local & 0xffffc000) | 0x00020000));

	/* Umnask global Interrupt in GAHBCFG and restore it */
	gahbcfg.d32 = gr->gahbcfg_local;
	gahbcfg.b.glblintrmsk = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gahbcfg, gahbcfg.d32);

	/* Clear all pending interupts */
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, 0xFFFFFFFF);

	/* Unmask restore done interrupt */
	gintmsk.b.restoredone = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintmsk, gintmsk.d32);

	/* Restore GUSBCFG and HCFG/DCFG */
	gusbcfg.d32 = core_if->gr_backup->gusbcfg_local;
	DWC_WRITE_REG32(&core_if->core_global_regs->gusbcfg, gusbcfg.d32);

	if (is_host) {
		hcfg_data_t hcfg = {.d32 = 0 };
		hcfg.d32 = core_if->hr_backup->hcfg_local;
		DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hcfg,
				hcfg.d32);

		/* Load restore values for [31:14] bits */
		pcgcctl.d32 = gr->pcgcctl_local & 0xffffc000;
		pcgcctl.d32 = gr->pcgcctl_local | 0x00020000;

		if (rmode)
			pcgcctl.b.restoremode = 1;
		DWC_WRITE_REG32(core_if->pcgcctl, pcgcctl.d32);
		dwc_udelay(10);

		/* Load restore values for [31:14] bits and set EssRegRestored bit */
		pcgcctl.d32 = gr->pcgcctl_local | 0xffffc000;
		pcgcctl.d32 = gr->pcgcctl_local & 0xffffc000;
		pcgcctl.b.ess_reg_restored = 1;
		if (rmode)
			pcgcctl.b.restoremode = 1;
		DWC_WRITE_REG32(core_if->pcgcctl, pcgcctl.d32);
	} else {
		dcfg_data_t dcfg = {.d32 = 0 };
		dcfg.d32 = core_if->dr_backup->dcfg;
		DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dcfg, dcfg.d32);

		/* Load restore values for [31:14] bits */
		pcgcctl.d32 = gr->pcgcctl_local & 0xffffc000;
		pcgcctl.d32 = gr->pcgcctl_local | 0x00020000;
		if (!rmode) {
			pcgcctl.d32 |= 0x208;
		}
		DWC_WRITE_REG32(core_if->pcgcctl, pcgcctl.d32);
		dwc_udelay(10);

		/* Load restore values for [31:14] bits */
		pcgcctl.d32 = gr->pcgcctl_local & 0xffffc000;
		pcgcctl.d32 = gr->pcgcctl_local | 0x00020000;
		pcgcctl.b.ess_reg_restored = 1;
		if (!rmode)
			pcgcctl.d32 |= 0x208;
		DWC_WRITE_REG32(core_if->pcgcctl, pcgcctl.d32);
	}

	return 0;
}