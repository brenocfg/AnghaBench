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
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* fops; } ;
typedef  TYPE_2__ dwc_otg_pcd_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* suspend ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int32_t dwc_otg_pcd_suspend_cb(void *p)
{
	dwc_otg_pcd_t *pcd = (dwc_otg_pcd_t *) p;

	if (pcd->fops->suspend) {
		DWC_SPINUNLOCK(pcd->lock);
		pcd->fops->suspend(pcd);
		DWC_SPINLOCK(pcd->lock);
	}

	return 1;
}