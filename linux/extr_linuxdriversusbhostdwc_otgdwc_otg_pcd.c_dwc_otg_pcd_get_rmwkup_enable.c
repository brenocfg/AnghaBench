#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int remote_wakeup_enable; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;

/* Variables and functions */

int dwc_otg_pcd_get_rmwkup_enable(dwc_otg_pcd_t * pcd)
{
	return pcd->remote_wakeup_enable;
}