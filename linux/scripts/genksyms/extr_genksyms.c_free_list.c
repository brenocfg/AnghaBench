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
 int /*<<< orphan*/  free_node (struct string_list*) ; 

void free_list(struct string_list *s, struct string_list *e)
{
	while (s != e) {
		struct string_list *next = s->next;
		free_node(s);
		s = next;
	}
}