#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int hs_phy_type; int fs_phy_type; } ;
struct TYPE_11__ {TYPE_1__ b; } ;
struct TYPE_16__ {TYPE_6__* dev_if; TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_13__ {int devspd; } ;
struct TYPE_17__ {int /*<<< orphan*/  d32; TYPE_4__ b; } ;
typedef  TYPE_8__ dcfg_data_t ;
struct TYPE_15__ {TYPE_5__* dev_global_regs; } ;
struct TYPE_14__ {int /*<<< orphan*/  dcfg; } ;
struct TYPE_12__ {scalar_t__ phy_type; scalar_t__ speed; scalar_t__ ulpi_fs_ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ DWC_SPEED_PARAM_FULL ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_devspd(dwc_otg_core_if_t * core_if)
{
	uint32_t val;
	dcfg_data_t dcfg;

	if (((core_if->hwcfg2.b.hs_phy_type == 2) &&
	     (core_if->hwcfg2.b.fs_phy_type == 1) &&
	     (core_if->core_params->ulpi_fs_ls)) ||
	    (core_if->core_params->phy_type == DWC_PHY_TYPE_PARAM_FS)) {
		/* Full speed PHY */
		val = 0x3;
	} else if (core_if->core_params->speed == DWC_SPEED_PARAM_FULL) {
		/* High speed PHY running at full speed */
		val = 0x1;
	} else {
		/* High speed PHY running at high speed */
		val = 0x0;
	}

	DWC_DEBUGPL(DBG_CIL, "Initializing DCFG.DevSpd to 0x%1x\n", val);

	dcfg.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dcfg);
	dcfg.b.devspd = val;
	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dcfg, dcfg.d32);
}