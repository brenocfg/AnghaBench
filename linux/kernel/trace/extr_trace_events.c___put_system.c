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
struct event_subsystem {int /*<<< orphan*/  name; struct event_subsystem* filter_string; int /*<<< orphan*/  list; struct event_subsystem* filter; } ;
struct event_filter {int /*<<< orphan*/  name; struct event_filter* filter_string; int /*<<< orphan*/  list; struct event_filter* filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct event_subsystem*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ system_refcount (struct event_subsystem*) ; 
 scalar_t__ system_refcount_dec (struct event_subsystem*) ; 

__attribute__((used)) static void __put_system(struct event_subsystem *system)
{
	struct event_filter *filter = system->filter;

	WARN_ON_ONCE(system_refcount(system) == 0);
	if (system_refcount_dec(system))
		return;

	list_del(&system->list);

	if (filter) {
		kfree(filter->filter_string);
		kfree(filter);
	}
	kfree_const(system->name);
	kfree(system);
}