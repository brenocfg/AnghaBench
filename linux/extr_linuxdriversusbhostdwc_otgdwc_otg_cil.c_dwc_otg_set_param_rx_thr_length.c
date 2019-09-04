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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {TYPE_1__* core_params; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/  rx_thr_length; } ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 

int dwc_otg_set_param_rx_thr_length(dwc_otg_core_if_t * core_if, int32_t val)
{
	if (DWC_OTG_PARAM_TEST(val, 8, 128)) {
		DWC_WARN("Wrong valaue for rx_thr_length\n");
		DWC_WARN("rx_thr_length must be 8 - 128\n");
		return -DWC_E_INVALID;
	}

	core_if->core_params->rx_thr_length = val;
	return 0;
}