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
typedef  int int32_t ;
struct TYPE_6__ {scalar_t__ i2c; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__* core_params; TYPE_2__ hwcfg3; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int i2c_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_i2c_enable(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;
	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN("Wrong valaue for i2c_enable\n");
		DWC_WARN("i2c_enable must be 0 or 1\n");
		return -DWC_E_INVALID;
	}
#ifndef NO_FS_PHY_HW_CHECK
	if (val == 1 && core_if->hwcfg3.b.i2c == 0) {
		if (dwc_otg_param_initialized(core_if->core_params->i2c_enable)) {
			DWC_ERROR
			    ("%d invalid for i2c_enable. Check HW configuration.\n",
			     val);
		}
		val = 0;
		retval = -DWC_E_INVALID;
	}
#endif

	core_if->core_params->i2c_enable = val;
	return retval;
}