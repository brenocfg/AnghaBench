#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_8__ {scalar_t__ xhiber; } ;
struct TYPE_10__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_4__ hwcfg4_data_t ;
struct TYPE_11__ {scalar_t__ snpsid; TYPE_3__* core_params; TYPE_1__* core_global_regs; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_9__ {int power_down; } ;
struct TYPE_7__ {int /*<<< orphan*/  ghwcfg4; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WARN (char*,...) ; 
 scalar_t__ OTG_CORE_REV_2_91a ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_power_down(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	int valid = 1;
	hwcfg4_data_t hwcfg4 = {.d32 = 0 };
	hwcfg4.d32 = DWC_READ_REG32(&core_if->core_global_regs->ghwcfg4);

	if (DWC_OTG_PARAM_TEST(val, 0, 3)) {
		DWC_WARN("`%d' invalid for parameter `power_down'\n", val);
		DWC_WARN("power_down must be 0 - 2\n");
		return -DWC_E_INVALID;
	}

	if ((val == 2) && (core_if->snpsid < OTG_CORE_REV_2_91a)) {
		valid = 0;
	}
	if ((val == 3)
	    && ((core_if->snpsid < OTG_CORE_REV_3_00a)
		|| (hwcfg4.b.xhiber == 0))) {
		valid = 0;
	}
	if (valid == 0) {
		if (dwc_otg_param_initialized(core_if->core_params->power_down)) {
			DWC_ERROR
			    ("%d invalid for parameter power_down. Check HW configuration.\n",
			     val);
		}
		retval = -DWC_E_INVALID;
		val = 0;
	}
	core_if->core_params->power_down = val;
	return retval;
}