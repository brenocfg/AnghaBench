#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int rc; struct TYPE_6__* next; int /*<<< orphan*/  data; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ spl_ptr_llist_element ;
struct TYPE_7__ {int /*<<< orphan*/  (* ctor ) (TYPE_1__*) ;int /*<<< orphan*/  count; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ spl_ptr_llist ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void spl_ptr_llist_push(spl_ptr_llist *llist, zval *data) /* {{{ */
{
	spl_ptr_llist_element *elem = emalloc(sizeof(spl_ptr_llist_element));

	elem->rc   = 1;
	elem->prev = llist->tail;
	elem->next = NULL;
	ZVAL_COPY_VALUE(&elem->data, data);

	if (llist->tail) {
		llist->tail->next = elem;
	} else {
		llist->head = elem;
	}

	llist->tail = elem;
	llist->count++;

	if (llist->ctor) {
		llist->ctor(elem);
	}
}