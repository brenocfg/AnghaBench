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
struct oxu_hcd {int /*<<< orphan*/  mem_lock; scalar_t__* qh_used; TYPE_1__* mem; } ;
struct ehci_qh {int dummy; } ;
struct TYPE_2__ {struct ehci_qh* qh_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxu_qh_free(struct oxu_hcd *oxu, struct ehci_qh *qh)
{
	int index;

	spin_lock(&oxu->mem_lock);

	index = qh - &oxu->mem->qh_pool[0];
	oxu->qh_used[index] = 0;

	spin_unlock(&oxu->mem_lock);
}