#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int irq_flags; TYPE_1__* ops; int /*<<< orphan*/  dev_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_irq ) () ;int /*<<< orphan*/  (* check_irq ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_2__* controller ; 
 int /*<<< orphan*/  cpci_thread ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
cpci_hp_intr(int irq, void *data)
{
	dbg("entered cpci_hp_intr");

	/* Check to see if it was our interrupt */
	if ((controller->irq_flags & IRQF_SHARED) &&
	    !controller->ops->check_irq(controller->dev_id)) {
		dbg("exited cpci_hp_intr, not our interrupt");
		return IRQ_NONE;
	}

	/* Disable ENUM interrupt */
	controller->ops->disable_irq();

	/* Trigger processing by the event thread */
	wake_up_process(cpci_thread);
	return IRQ_HANDLED;
}