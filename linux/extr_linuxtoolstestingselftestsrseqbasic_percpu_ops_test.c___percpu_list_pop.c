#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct percpu_list_node {struct percpu_list_node* next; } ;
struct percpu_list {TYPE_1__* c; } ;
struct TYPE_2__ {struct percpu_list_node* head; } ;

/* Variables and functions */

struct percpu_list_node *__percpu_list_pop(struct percpu_list *list, int cpu)
{
	struct percpu_list_node *node;

	node = list->c[cpu].head;
	if (!node)
		return NULL;
	list->c[cpu].head = node->next;
	return node;
}