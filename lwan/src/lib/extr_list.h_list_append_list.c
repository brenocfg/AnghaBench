#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_node {TYPE_2__* next; } ;
struct TYPE_5__ {struct list_node* prev; } ;
struct list_head {TYPE_2__ n; } ;
struct TYPE_4__ {struct list_node* prev; } ;
struct TYPE_6__ {TYPE_1__ n; } ;

/* Variables and functions */
 TYPE_3__* list_debug (struct list_head*) ; 
 int /*<<< orphan*/  list_del (TYPE_2__*) ; 
 int /*<<< orphan*/  list_head_init (struct list_head*) ; 

__attribute__((used)) static inline void list_append_list(struct list_head *to,
				    struct list_head *from)
{
	struct list_node *from_tail = list_debug(from)->n.prev;
	struct list_node *to_tail = list_debug(to)->n.prev;

	/* Sew in head and entire list. */
	to->n.prev = from_tail;
	from_tail->next = &to->n;
	to_tail->next = &from->n;
	from->n.prev = to_tail;

	/* Now remove head. */
	list_del(&from->n);
	list_head_init(from);
}