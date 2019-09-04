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
struct irq_domain {int flags; struct irq_domain* name; int /*<<< orphan*/  link; int /*<<< orphan*/  revmap_tree; } ;

/* Variables and functions */
 int IRQ_DOMAIN_NAME_ALLOCATED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  debugfs_remove_domain_dir (struct irq_domain*) ; 
 struct irq_domain* irq_default_domain ; 
 int /*<<< orphan*/  irq_domain_get_of_node (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_domain_mutex ; 
 int /*<<< orphan*/  irq_set_default_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct irq_domain*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct irq_domain*) ; 
 int /*<<< orphan*/  radix_tree_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void irq_domain_remove(struct irq_domain *domain)
{
	mutex_lock(&irq_domain_mutex);
	debugfs_remove_domain_dir(domain);

	WARN_ON(!radix_tree_empty(&domain->revmap_tree));

	list_del(&domain->link);

	/*
	 * If the going away domain is the default one, reset it.
	 */
	if (unlikely(irq_default_domain == domain))
		irq_set_default_host(NULL);

	mutex_unlock(&irq_domain_mutex);

	pr_debug("Removed domain %s\n", domain->name);

	of_node_put(irq_domain_get_of_node(domain));
	if (domain->flags & IRQ_DOMAIN_NAME_ALLOCATED)
		kfree(domain->name);
	kfree(domain);
}