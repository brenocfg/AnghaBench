#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_qh_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dwc_otg_hcd_qh_remove_and_free(dwc_otg_hcd_t * hcd,
						  dwc_otg_qh_t * qh)
{
	dwc_irqflags_t flags;
	DWC_SPINLOCK_IRQSAVE(hcd->lock, &flags);
	dwc_otg_hcd_qh_remove(hcd, qh);
	DWC_SPINUNLOCK_IRQRESTORE(hcd->lock, flags);
	dwc_otg_hcd_qh_free(hcd, qh);
}