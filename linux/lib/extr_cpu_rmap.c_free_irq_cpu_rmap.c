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
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct irq_glue {TYPE_1__ notify; } ;
struct cpu_rmap {size_t used; struct irq_glue** obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_rmap_put (struct cpu_rmap*) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void free_irq_cpu_rmap(struct cpu_rmap *rmap)
{
	struct irq_glue *glue;
	u16 index;

	if (!rmap)
		return;

	for (index = 0; index < rmap->used; index++) {
		glue = rmap->obj[index];
		irq_set_affinity_notifier(glue->notify.irq, NULL);
	}

	cpu_rmap_put(rmap);
}