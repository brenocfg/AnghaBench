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
struct cond_node {struct cond_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_node_destroy (struct cond_node*) ; 

__attribute__((used)) static void cond_list_destroy(struct cond_node *list)
{
	struct cond_node *next, *cur;

	if (list == NULL)
		return;

	for (cur = list; cur; cur = next) {
		next = cur->next;
		cond_node_destroy(cur);
	}
}