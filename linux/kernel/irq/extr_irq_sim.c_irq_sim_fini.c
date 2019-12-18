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
struct TYPE_2__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  work; } ;
struct irq_sim {int /*<<< orphan*/  irqs; int /*<<< orphan*/  irq_count; int /*<<< orphan*/  irq_base; TYPE_1__ work_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_free_descs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void irq_sim_fini(struct irq_sim *sim)
{
	irq_work_sync(&sim->work_ctx.work);
	bitmap_free(sim->work_ctx.pending);
	irq_free_descs(sim->irq_base, sim->irq_count);
	kfree(sim->irqs);
}