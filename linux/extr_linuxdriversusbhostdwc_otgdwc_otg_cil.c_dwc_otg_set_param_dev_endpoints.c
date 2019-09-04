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
struct TYPE_7__ {scalar_t__ num_dev_ep; } ;
struct TYPE_8__ {TYPE_2__ b; } ;
struct TYPE_9__ {TYPE_1__* core_params; TYPE_3__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_6__ {scalar_t__ dev_endpoints; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,scalar_t__) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (scalar_t__,int,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (scalar_t__) ; 

int dwc_otg_set_param_dev_endpoints(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;

	if (DWC_OTG_PARAM_TEST(val, 1, 15)) {
		DWC_WARN("Wrong value for dev_endpoints\n");
		DWC_WARN("dev_endpoints must be 1-15\n");
		return -DWC_E_INVALID;
	}

	if (val > (core_if->hwcfg2.b.num_dev_ep)) {
		if (dwc_otg_param_initialized
		    (core_if->core_params->dev_endpoints)) {
			DWC_ERROR
			    ("%d invalid for dev_endpoints. Check HW configurations.\n",
			     val);
		}
		val = core_if->hwcfg2.b.num_dev_ep;
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->dev_endpoints = val;
	return retval;
}