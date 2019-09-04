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
struct irq_domain {size_t revmap_size; int /*<<< orphan*/  revmap_tree_mutex; int /*<<< orphan*/  revmap_tree; scalar_t__* linear_revmap; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void irq_domain_clear_mapping(struct irq_domain *domain,
				     irq_hw_number_t hwirq)
{
	if (hwirq < domain->revmap_size) {
		domain->linear_revmap[hwirq] = 0;
	} else {
		mutex_lock(&domain->revmap_tree_mutex);
		radix_tree_delete(&domain->revmap_tree, hwirq);
		mutex_unlock(&domain->revmap_tree_mutex);
	}
}