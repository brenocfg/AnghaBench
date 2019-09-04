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
struct irqaction {scalar_t__ (* thread_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev_id; int /*<<< orphan*/  irq; } ;
struct irq_desc {int /*<<< orphan*/  threads_handled; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_finalize_oneshot (struct irq_desc*,struct irqaction*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t irq_thread_fn(struct irq_desc *desc,
		struct irqaction *action)
{
	irqreturn_t ret;

	ret = action->thread_fn(action->irq, action->dev_id);
	if (ret == IRQ_HANDLED)
		atomic_inc(&desc->threads_handled);

	irq_finalize_oneshot(desc, action);
	return ret;
}