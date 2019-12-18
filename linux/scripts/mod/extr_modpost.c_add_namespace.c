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
struct namespace_list {struct namespace_list* next; int /*<<< orphan*/  namespace; } ;

/* Variables and functions */
 struct namespace_list* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contains_namespace (struct namespace_list*,char const*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void add_namespace(struct namespace_list **list, const char *namespace)
{
	struct namespace_list *ns_entry;

	if (!contains_namespace(*list, namespace)) {
		ns_entry = NOFAIL(malloc(sizeof(struct namespace_list) +
					 strlen(namespace) + 1));
		strcpy(ns_entry->namespace, namespace);
		ns_entry->next = *list;
		*list = ns_entry;
	}
}