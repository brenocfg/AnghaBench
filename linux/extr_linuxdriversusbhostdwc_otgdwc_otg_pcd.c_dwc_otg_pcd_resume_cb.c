#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_9__ {TYPE_1__* fops; } ;
typedef  TYPE_3__ dwc_otg_pcd_t ;
struct TYPE_10__ {int /*<<< orphan*/  srp_timer; scalar_t__ srp_timer_started; TYPE_2__* core_params; } ;
struct TYPE_8__ {scalar_t__ phy_type; int /*<<< orphan*/  i2c_enable; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC_TIMER_CANCEL (int /*<<< orphan*/ ) ; 
 TYPE_5__* GET_CORE_IF (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int32_t dwc_otg_pcd_resume_cb(void *p)
{
	dwc_otg_pcd_t *pcd = (dwc_otg_pcd_t *) p;

	if (pcd->fops->resume) {
		pcd->fops->resume(pcd);
	}

	/* Stop the SRP timeout timer. */
	if ((GET_CORE_IF(pcd)->core_params->phy_type != DWC_PHY_TYPE_PARAM_FS)
	    || (!GET_CORE_IF(pcd)->core_params->i2c_enable)) {
		if (GET_CORE_IF(pcd)->srp_timer_started) {
			GET_CORE_IF(pcd)->srp_timer_started = 0;
			DWC_TIMER_CANCEL(GET_CORE_IF(pcd)->srp_timer);
		}
	}
	return 1;
}