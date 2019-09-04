#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {scalar_t__ architecture; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_10__ {TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 
 int /*<<< orphan*/  dwc_otg_set_param_dma_desc_enable (TYPE_4__*,int /*<<< orphan*/ ) ; 

int dwc_otg_set_param_dma_enable(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN("Wrong value for dma enable\n");
		return -DWC_E_INVALID;
	}

	if ((val == 1) && (core_if->hwcfg2.b.architecture == 0)) {
		if (dwc_otg_param_initialized(core_if->core_params->dma_enable)) {
			DWC_ERROR
			    ("%d invalid for dma_enable paremter. Check HW configuration.\n",
			     val);
		}
		val = 0;
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->dma_enable = val;
	if (val == 0) {
		dwc_otg_set_param_dma_desc_enable(core_if, 0);
	}
	return retval;
}