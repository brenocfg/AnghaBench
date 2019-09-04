#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CORE_IF (int /*<<< orphan*/ *) ; 
 int dwc_otg_get_frame_number (int /*<<< orphan*/ ) ; 

int dwc_otg_pcd_get_frame_number(dwc_otg_pcd_t * pcd)
{
	return dwc_otg_get_frame_number(GET_CORE_IF(pcd));
}