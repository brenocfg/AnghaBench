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
struct string_list {struct string_list* next; } ;

/* Variables and functions */
 void* copy_node (struct string_list*) ; 

struct string_list *copy_list_range(struct string_list *start,
				    struct string_list *end)
{
	struct string_list *res, *n;

	if (start == end)
		return NULL;
	n = res = copy_node(start);
	for (start = start->next; start != end; start = start->next) {
		n->next = copy_node(start);
		n = n->next;
	}
	n->next = NULL;
	return res;
}