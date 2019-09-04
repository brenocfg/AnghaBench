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
struct uhci_qh {int /*<<< orphan*/  node; } ;
struct uhci_hcd {TYPE_1__* skel_iso_qh; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void link_iso(struct uhci_hcd *uhci, struct uhci_qh *qh)
{
	list_add_tail(&qh->node, &uhci->skel_iso_qh->node);

	/* Isochronous QHs aren't linked by the hardware */
}