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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_6__ {int hs_phy_type; int fs_phy_type; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__* core_params; TYPE_2__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {scalar_t__ speed; scalar_t__ ulpi_fs_ls; } ;

/* Variables and functions */
 scalar_t__ DWC_SPEED_PARAM_FULL ; 
 TYPE_4__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

uint32_t dwc_otg_pcd_is_dualspeed(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);

	if ((core_if->core_params->speed == DWC_SPEED_PARAM_FULL) ||
	    ((core_if->hwcfg2.b.hs_phy_type == 2) &&
	     (core_if->hwcfg2.b.fs_phy_type == 1) &&
	     (core_if->core_params->ulpi_fs_ls))) {
		return 0;
	}

	return 1;
}