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
struct resource {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  name; scalar_t__ parent; } ;

/* Variables and functions */
 struct resource* __insert_resource (struct resource*,struct resource*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void insert_resource_expand_to_fit(struct resource *root, struct resource *new)
{
	if (new->parent)
		return;

	write_lock(&resource_lock);
	for (;;) {
		struct resource *conflict;

		conflict = __insert_resource(root, new);
		if (!conflict)
			break;
		if (conflict == root)
			break;

		/* Ok, expand resource to cover the conflict, then try again .. */
		if (conflict->start < new->start)
			new->start = conflict->start;
		if (conflict->end > new->end)
			new->end = conflict->end;

		printk("Expanded resource %s due to conflict with %s\n", new->name, conflict->name);
	}
	write_unlock(&resource_lock);
}