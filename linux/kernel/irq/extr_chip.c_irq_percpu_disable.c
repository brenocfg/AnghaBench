#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* chip; } ;
struct irq_desc {int /*<<< orphan*/  percpu_enabled; TYPE_2__ irq_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_mask ) (TYPE_2__*) ;int /*<<< orphan*/  (* irq_disable ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

void irq_percpu_disable(struct irq_desc *desc, unsigned int cpu)
{
	if (desc->irq_data.chip->irq_disable)
		desc->irq_data.chip->irq_disable(&desc->irq_data);
	else
		desc->irq_data.chip->irq_mask(&desc->irq_data);
	cpumask_clear_cpu(cpu, desc->percpu_enabled);
}