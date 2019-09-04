#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* fops; scalar_t__ a_alt_hnp_support; scalar_t__ a_hnp_support; scalar_t__ b_hnp_enable; } ;
typedef  TYPE_2__ dwc_otg_pcd_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* hnp_changed ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void dwc_otg_pcd_update_otg(dwc_otg_pcd_t * pcd, const unsigned reset)
{

	if (reset) {
		pcd->b_hnp_enable = 0;
		pcd->a_hnp_support = 0;
		pcd->a_alt_hnp_support = 0;
	}

	if (pcd->fops->hnp_changed) {
		pcd->fops->hnp_changed(pcd);
	}
}