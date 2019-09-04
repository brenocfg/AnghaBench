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
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int hs_phy_type; int fs_phy_type; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {scalar_t__ phy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,scalar_t__) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_ULPI ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_UTMI ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (scalar_t__) ; 

int dwc_otg_set_param_phy_type(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	int valid = 0;

	if (DWC_OTG_PARAM_TEST(val, 0, 2)) {
		DWC_WARN("Wrong value for phy_type\n");
		DWC_WARN("phy_type must be 0,1 or 2\n");
		return -DWC_E_INVALID;
	}
#ifndef NO_FS_PHY_HW_CHECKS
	if ((val == DWC_PHY_TYPE_PARAM_UTMI) &&
	    ((core_if->hwcfg2.b.hs_phy_type == 1) ||
	     (core_if->hwcfg2.b.hs_phy_type == 3))) {
		valid = 1;
	} else if ((val == DWC_PHY_TYPE_PARAM_ULPI) &&
		   ((core_if->hwcfg2.b.hs_phy_type == 2) ||
		    (core_if->hwcfg2.b.hs_phy_type == 3))) {
		valid = 1;
	} else if ((val == DWC_PHY_TYPE_PARAM_FS) &&
		   (core_if->hwcfg2.b.fs_phy_type == 1)) {
		valid = 1;
	}
	if (!valid) {
		if (dwc_otg_param_initialized(core_if->core_params->phy_type)) {
			DWC_ERROR
			    ("%d invalid for phy_type. Check HW configurations.\n",
			     val);
		}
		if (core_if->hwcfg2.b.hs_phy_type) {
			if ((core_if->hwcfg2.b.hs_phy_type == 3) ||
			    (core_if->hwcfg2.b.hs_phy_type == 1)) {
				val = DWC_PHY_TYPE_PARAM_UTMI;
			} else {
				val = DWC_PHY_TYPE_PARAM_ULPI;
			}
		}
		retval = -DWC_E_INVALID;
	}
#endif
	core_if->core_params->phy_type = val;
	return retval;
}