#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {TYPE_1__* core_params; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_5__ {scalar_t__ host_ls_low_power_phy_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,scalar_t__) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_48MHZ ; 
 scalar_t__ DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_6MHZ ; 
 scalar_t__ DWC_OTG_PARAM_TEST (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_get_param_phy_type (TYPE_2__*) ; 
 scalar_t__ dwc_otg_param_initialized (scalar_t__) ; 

int dwc_otg_set_param_host_ls_low_power_phy_clk(dwc_otg_core_if_t * core_if,
						int32_t val)
{
	int retval = 0;

	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN
		    ("Wrong value for host_ls_low_power_phy_clk parameter\n");
		DWC_WARN("host_ls_low_power_phy_clk must be 0 or 1\n");
		return -DWC_E_INVALID;
	}

	if ((val == DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_48MHZ)
	    && (dwc_otg_get_param_phy_type(core_if) == DWC_PHY_TYPE_PARAM_FS)) {
		if (dwc_otg_param_initialized
		    (core_if->core_params->host_ls_low_power_phy_clk)) {
			DWC_ERROR
			    ("%d invalid for host_ls_low_power_phy_clk. Check HW configuration.\n",
			     val);
		}
		val =
		    (dwc_otg_get_param_phy_type(core_if) ==
		     DWC_PHY_TYPE_PARAM_FS) ?
		    DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_6MHZ :
		    DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_48MHZ;
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->host_ls_low_power_phy_clk = val;
	return retval;
}