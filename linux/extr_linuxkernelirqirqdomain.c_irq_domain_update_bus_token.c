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
struct irq_domain {int bus_token; char* name; int flags; } ;
typedef  enum irq_domain_bus_token { ____Placeholder_irq_domain_bus_token } irq_domain_bus_token ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_DOMAIN_NAME_ALLOCATED ; 
 int /*<<< orphan*/  debugfs_add_domain_dir (struct irq_domain*) ; 
 int /*<<< orphan*/  debugfs_remove_domain_dir (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_domain_mutex ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void irq_domain_update_bus_token(struct irq_domain *domain,
				 enum irq_domain_bus_token bus_token)
{
	char *name;

	if (domain->bus_token == bus_token)
		return;

	mutex_lock(&irq_domain_mutex);

	domain->bus_token = bus_token;

	name = kasprintf(GFP_KERNEL, "%s-%d", domain->name, bus_token);
	if (!name) {
		mutex_unlock(&irq_domain_mutex);
		return;
	}

	debugfs_remove_domain_dir(domain);

	if (domain->flags & IRQ_DOMAIN_NAME_ALLOCATED)
		kfree(domain->name);
	else
		domain->flags |= IRQ_DOMAIN_NAME_ALLOCATED;

	domain->name = name;
	debugfs_add_domain_dir(domain);

	mutex_unlock(&irq_domain_mutex);
}