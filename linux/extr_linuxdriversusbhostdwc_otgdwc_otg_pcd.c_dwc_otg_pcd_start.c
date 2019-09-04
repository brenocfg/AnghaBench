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
struct dwc_otg_pcd_function_ops {int dummy; } ;
struct TYPE_3__ {struct dwc_otg_pcd_function_ops const* fops; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;

/* Variables and functions */

void dwc_otg_pcd_start(dwc_otg_pcd_t * pcd,
		       const struct dwc_otg_pcd_function_ops *fops)
{
	pcd->fops = fops;
}