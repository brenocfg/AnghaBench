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
struct switch_attr {struct switch_attr* description; struct switch_attr* name; struct switch_attr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct switch_attr*) ; 

__attribute__((used)) static void
swlib_free_attributes(struct switch_attr **head)
{
	struct switch_attr *a = *head;
	struct switch_attr *next;

	while (a) {
		next = a->next;
		free(a->name);
		free(a->description);
		free(a);
		a = next;
	}
	*head = NULL;
}