#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CORE_IF (TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_initiate_srp (int /*<<< orphan*/ ) ; 

void dwc_otg_pcd_initiate_srp(dwc_otg_pcd_t * pcd)
{
	dwc_irqflags_t flags;
	DWC_SPINLOCK_IRQSAVE(pcd->lock, &flags);
	dwc_otg_initiate_srp(GET_CORE_IF(pcd));
	DWC_SPINUNLOCK_IRQRESTORE(pcd->lock, flags);
}