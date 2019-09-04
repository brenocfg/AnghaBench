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
typedef  int int32_t ;
struct TYPE_5__ {scalar_t__ snpsid; TYPE_1__* core_params; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int cont_on_bna; int /*<<< orphan*/  dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*,...) ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_cont_on_bna(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	int valid = 1;

	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN("`%d' invalid for parameter `cont_on_bna'\n", val);
		DWC_WARN("cont_on_bna must be 0 or 1\n");
		return -DWC_E_INVALID;
	}

	if ((val == 1) && ((core_if->snpsid < OTG_CORE_REV_2_94a) ||
		!(core_if->core_params->dma_desc_enable))) {
			valid = 0;
	}
	if (valid == 0) {
		if (dwc_otg_param_initialized(core_if->core_params->cont_on_bna)) {
			DWC_ERROR("%d invalid for parameter cont_on_bna."
				"Check HW configuration.\n", val);
		}
		retval = -DWC_E_INVALID;
		val = 0;
	}
	core_if->core_params->cont_on_bna = val;
	return retval;
}