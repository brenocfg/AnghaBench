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
struct tlpm_node {struct tlpm_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tlpm_node*) ; 

__attribute__((used)) static void tlpm_clear(struct tlpm_node *list)
{
	struct tlpm_node *node;

	/* free all entries in @list */

	while ((node = list)) {
		list = list->next;
		free(node);
	}
}