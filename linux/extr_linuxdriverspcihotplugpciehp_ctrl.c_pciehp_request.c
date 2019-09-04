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
struct controller {TYPE_1__* pcie; int /*<<< orphan*/  pending_events; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_wake_thread (int /*<<< orphan*/ ,struct controller*) ; 
 int /*<<< orphan*/  pciehp_poll_mode ; 

void pciehp_request(struct controller *ctrl, int action)
{
	atomic_or(action, &ctrl->pending_events);
	if (!pciehp_poll_mode)
		irq_wake_thread(ctrl->pcie->irq, ctrl);
}