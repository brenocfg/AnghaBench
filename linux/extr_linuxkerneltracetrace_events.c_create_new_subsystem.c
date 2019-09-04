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
struct event_subsystem {int ref_count; int /*<<< orphan*/  name; int /*<<< orphan*/  list; int /*<<< orphan*/ * filter; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  event_subsystems ; 
 int /*<<< orphan*/  kfree (struct event_subsystem*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 struct event_subsystem* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct event_subsystem *
create_new_subsystem(const char *name)
{
	struct event_subsystem *system;

	/* need to create new entry */
	system = kmalloc(sizeof(*system), GFP_KERNEL);
	if (!system)
		return NULL;

	system->ref_count = 1;

	/* Only allocate if dynamic (kprobes and modules) */
	system->name = kstrdup_const(name, GFP_KERNEL);
	if (!system->name)
		goto out_free;

	system->filter = NULL;

	system->filter = kzalloc(sizeof(struct event_filter), GFP_KERNEL);
	if (!system->filter)
		goto out_free;

	list_add(&system->list, &event_subsystems);

	return system;

 out_free:
	kfree_const(system->name);
	kfree(system);
	return NULL;
}