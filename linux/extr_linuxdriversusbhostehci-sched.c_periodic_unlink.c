#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union ehci_shadow {void* ptr; } ;
struct ehci_hcd {scalar_t__* periodic; TYPE_1__* dummy; int /*<<< orphan*/  use_dummy_qh; union ehci_shadow* pshadow; } ;
typedef  scalar_t__ __hc32 ;
struct TYPE_2__ {int /*<<< orphan*/  qh_dma; } ;

/* Variables and functions */
 scalar_t__ EHCI_LIST_END (struct ehci_hcd*) ; 
 int /*<<< orphan*/  Q_NEXT_TYPE (struct ehci_hcd*,scalar_t__) ; 
 scalar_t__ cpu_to_hc32 (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 union ehci_shadow* periodic_next_shadow (struct ehci_hcd*,union ehci_shadow*,int /*<<< orphan*/ ) ; 
 scalar_t__* shadow_next_periodic (struct ehci_hcd*,union ehci_shadow*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void periodic_unlink(struct ehci_hcd *ehci, unsigned frame, void *ptr)
{
	union ehci_shadow	*prev_p = &ehci->pshadow[frame];
	__hc32			*hw_p = &ehci->periodic[frame];
	union ehci_shadow	here = *prev_p;

	/* find predecessor of "ptr"; hw and shadow lists are in sync */
	while (here.ptr && here.ptr != ptr) {
		prev_p = periodic_next_shadow(ehci, prev_p,
				Q_NEXT_TYPE(ehci, *hw_p));
		hw_p = shadow_next_periodic(ehci, &here,
				Q_NEXT_TYPE(ehci, *hw_p));
		here = *prev_p;
	}
	/* an interrupt entry (at list end) could have been shared */
	if (!here.ptr)
		return;

	/* update shadow and hardware lists ... the old "next" pointers
	 * from ptr may still be in use, the caller updates them.
	 */
	*prev_p = *periodic_next_shadow(ehci, &here,
			Q_NEXT_TYPE(ehci, *hw_p));

	if (!ehci->use_dummy_qh ||
	    *shadow_next_periodic(ehci, &here, Q_NEXT_TYPE(ehci, *hw_p))
			!= EHCI_LIST_END(ehci))
		*hw_p = *shadow_next_periodic(ehci, &here,
				Q_NEXT_TYPE(ehci, *hw_p));
	else
		*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
}