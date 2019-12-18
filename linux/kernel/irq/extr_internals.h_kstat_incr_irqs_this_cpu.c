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
struct irq_desc {int /*<<< orphan*/  tot_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kstat_incr_irqs_this_cpu (struct irq_desc*) ; 

__attribute__((used)) static inline void kstat_incr_irqs_this_cpu(struct irq_desc *desc)
{
	__kstat_incr_irqs_this_cpu(desc);
	desc->tot_count++;
}