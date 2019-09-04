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
struct TYPE_6__ {int packet_size_cntr_width; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__* core_params; TYPE_2__ hwcfg3; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int max_packet_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int,int,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 scalar_t__ dwc_otg_param_initialized (int) ; 

int dwc_otg_set_param_max_packet_count(dwc_otg_core_if_t * core_if, int32_t val)
{
	int retval = 0;

	if (DWC_OTG_PARAM_TEST(val, 15, 511)) {
		DWC_WARN("Wrong value for max_packet_count\n");
		DWC_WARN("max_packet_count must be 15-511\n");
		return -DWC_E_INVALID;
	}

	if (val > (1 << (core_if->hwcfg3.b.packet_size_cntr_width + 4))) {
		if (dwc_otg_param_initialized
		    (core_if->core_params->max_packet_count)) {
			DWC_ERROR
			    ("%d invalid for max_packet_count. Check HW configuration.\n",
			     val);
		}
		val =
		    ((1 << (core_if->hwcfg3.b.packet_size_cntr_width + 4)) - 1);
		retval = -DWC_E_INVALID;
	}

	core_if->core_params->max_packet_count = val;
	return retval;
}