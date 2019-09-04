#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_4__ {TYPE_1__* core_params; } ;
struct TYPE_3__ {int lpm_enable; } ;

/* Variables and functions */
 TYPE_2__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

int dwc_otg_pcd_is_lpm_enabled(dwc_otg_pcd_t * pcd)
{
	return GET_CORE_IF(pcd)->core_params->lpm_enable;
}