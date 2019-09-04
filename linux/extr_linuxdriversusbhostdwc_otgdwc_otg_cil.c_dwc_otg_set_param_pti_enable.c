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
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ snpsid; TYPE_1__* core_params; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {scalar_t__ pti_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,scalar_t__) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*,scalar_t__) ; 
 scalar_t__ OTG_CORE_REV_2_72a ; 
 scalar_t__ dwc_otg_param_initialized (scalar_t__) ; 

int dwc_otg_set_param_pti_enable(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN("`%d' invalid for parameter `pti_enable'\n", val);
		return -DWC_E_INVALID;
	}
	if (val && (core_if->snpsid < OTG_CORE_REV_2_72a)) {
		if (dwc_otg_param_initialized(core_if->core_params->pti_enable)) {
			DWC_ERROR
			    ("%d invalid for parameter pti_enable. Check HW configuration.\n",
			     val);
		}
		retval = -DWC_E_INVALID;
		val = 0;
	}
	core_if->core_params->pti_enable = val;
	return retval;
}