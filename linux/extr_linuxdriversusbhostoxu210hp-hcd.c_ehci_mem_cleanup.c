#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct oxu_hcd {int /*<<< orphan*/ * pshadow; int /*<<< orphan*/ * periodic; int /*<<< orphan*/  urb_timer; int /*<<< orphan*/ * async; int /*<<< orphan*/ * murb_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_mem_cleanup(struct oxu_hcd *oxu)
{
	kfree(oxu->murb_pool);
	oxu->murb_pool = NULL;

	if (oxu->async)
		qh_put(oxu->async);
	oxu->async = NULL;

	del_timer(&oxu->urb_timer);

	oxu->periodic = NULL;

	/* shadow periodic table */
	kfree(oxu->pshadow);
	oxu->pshadow = NULL;
}