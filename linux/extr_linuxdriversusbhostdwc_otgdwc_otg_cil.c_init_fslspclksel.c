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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  fslspclksel; } ;
struct TYPE_16__ {int /*<<< orphan*/  d32; TYPE_4__ b; } ;
typedef  TYPE_7__ hcfg_data_t ;
struct TYPE_10__ {int hs_phy_type; int fs_phy_type; } ;
struct TYPE_11__ {TYPE_1__ b; } ;
struct TYPE_17__ {TYPE_6__* host_if; TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_15__ {TYPE_5__* host_global_regs; } ;
struct TYPE_14__ {int /*<<< orphan*/  hcfg; } ;
struct TYPE_12__ {scalar_t__ phy_type; scalar_t__ ulpi_fs_ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_HCFG_30_60_MHZ ; 
 int /*<<< orphan*/  DWC_HCFG_48_MHZ ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_fslspclksel(dwc_otg_core_if_t * core_if)
{
	uint32_t val;
	hcfg_data_t hcfg;

	if (((core_if->hwcfg2.b.hs_phy_type == 2) &&
	     (core_if->hwcfg2.b.fs_phy_type == 1) &&
	     (core_if->core_params->ulpi_fs_ls)) ||
	    (core_if->core_params->phy_type == DWC_PHY_TYPE_PARAM_FS)) {
		/* Full speed PHY */
		val = DWC_HCFG_48_MHZ;
	} else {
		/* High speed PHY running at full speed or high speed */
		val = DWC_HCFG_30_60_MHZ;
	}

	DWC_DEBUGPL(DBG_CIL, "Initializing HCFG.FSLSPClkSel to 0x%1x\n", val);
	hcfg.d32 = DWC_READ_REG32(&core_if->host_if->host_global_regs->hcfg);
	hcfg.b.fslspclksel = val;
	DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hcfg, hcfg.d32);
}