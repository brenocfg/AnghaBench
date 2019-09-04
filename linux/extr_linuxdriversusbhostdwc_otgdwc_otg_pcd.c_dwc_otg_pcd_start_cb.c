#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;

/* Variables and functions */
 TYPE_2__* GET_CORE_IF (TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_core_dev_init (TYPE_2__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_2__*) ; 

__attribute__((used)) static int32_t dwc_otg_pcd_start_cb(void *p)
{
	dwc_otg_pcd_t *pcd = (dwc_otg_pcd_t *) p;
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);

	/*
	 * Initialized the Core for Device mode.
	 */
	if (dwc_otg_is_device_mode(core_if)) {
		dwc_otg_core_dev_init(core_if);
		/* Set core_if's lock pointer to the pcd->lock */
		core_if->lock = pcd->lock;
	}
	return 1;
}