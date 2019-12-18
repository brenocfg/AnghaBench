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
struct nn_list_item {struct nn_list_item* next; TYPE_1__* prev; } ;
struct nn_list {TYPE_1__* last; struct nn_list_item* first; } ;
struct TYPE_2__ {struct nn_list_item* next; } ;

/* Variables and functions */
 void* NN_LIST_NOTINLIST ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_list_item_isinlist (struct nn_list_item*) ; 

struct nn_list_item *nn_list_erase (struct nn_list *self,
    struct nn_list_item *item)
{
    struct nn_list_item *next;

    nn_assert (nn_list_item_isinlist (item));

    if (item->prev)
        item->prev->next = item->next;
    else
        self->first = item->next;
    if (item->next)
        item->next->prev = item->prev;
    else
        self->last = item->prev;

    next = item->next;

    item->prev = NN_LIST_NOTINLIST;
    item->next = NN_LIST_NOTINLIST;

    return next;
}