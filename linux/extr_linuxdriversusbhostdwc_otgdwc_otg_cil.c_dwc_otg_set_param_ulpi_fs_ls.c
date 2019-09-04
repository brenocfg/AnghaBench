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
struct TYPE_4__ {int /*<<< orphan*/  ulpi_fs_ls; } ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 scalar_t__ DWC_OTG_PARAM_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 

int dwc_otg_set_param_ulpi_fs_ls(dwc_otg_core_if_t * core_if, int32_t val)
{
	if (DWC_OTG_PARAM_TEST(val, 0, 1)) {
		DWC_WARN("Wrong valaue for ulpi_fs_ls\n");
		DWC_WARN("ulpi_fs_ls must be 0 or 1\n");
		return -DWC_E_INVALID;
	}

	core_if->core_params->ulpi_fs_ls = val;
	return 0;
}