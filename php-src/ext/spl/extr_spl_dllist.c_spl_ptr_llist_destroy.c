#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ spl_ptr_llist_element ;
typedef  int /*<<< orphan*/  (* spl_ptr_llist_dtor_func ) (TYPE_1__*) ;
struct TYPE_8__ {int /*<<< orphan*/  (* dtor ) (TYPE_1__*) ;TYPE_1__* head; } ;
typedef  TYPE_3__ spl_ptr_llist ;

/* Variables and functions */
 int /*<<< orphan*/  SPL_LLIST_DELREF (TYPE_1__*) ; 
 int /*<<< orphan*/  efree (TYPE_3__*) ; 

__attribute__((used)) static void spl_ptr_llist_destroy(spl_ptr_llist *llist) /* {{{ */
{
	spl_ptr_llist_element   *current = llist->head, *next;
	spl_ptr_llist_dtor_func  dtor    = llist->dtor;

	while (current) {
		next = current->next;
		if (dtor) {
			dtor(current);
		}
		SPL_LLIST_DELREF(current);
		current = next;
	}

	efree(llist);
}