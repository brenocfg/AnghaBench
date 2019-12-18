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
struct namespace_list {int /*<<< orphan*/  namespace; struct namespace_list* next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool contains_namespace(struct namespace_list *list,
			       const char *namespace)
{
	struct namespace_list *ns_entry;

	for (ns_entry = list; ns_entry != NULL; ns_entry = ns_entry->next)
		if (strcmp(ns_entry->namespace, namespace) == 0)
			return true;

	return false;
}