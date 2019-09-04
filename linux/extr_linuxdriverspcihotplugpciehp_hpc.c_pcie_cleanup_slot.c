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
struct slot {int /*<<< orphan*/  work; } ;
struct controller {struct slot* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 

__attribute__((used)) static void pcie_cleanup_slot(struct controller *ctrl)
{
	struct slot *slot = ctrl->slot;

	cancel_delayed_work_sync(&slot->work);
	kfree(slot);
}