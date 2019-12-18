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
struct TYPE_6__ {int /*<<< orphan*/  data; struct TYPE_6__* next; } ;
typedef  TYPE_1__ spl_ptr_llist_element ;
struct TYPE_7__ {TYPE_1__* head; } ;
typedef  TYPE_2__ spl_ptr_llist ;

/* Variables and functions */
 int /*<<< orphan*/  spl_ptr_llist_push (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_ptr_llist_copy(spl_ptr_llist *from, spl_ptr_llist *to) /* {{{ */
{
	spl_ptr_llist_element *current = from->head, *next;
//???	spl_ptr_llist_ctor_func ctor = from->ctor;

	while (current) {
		next = current->next;

		/*??? FIXME
		if (ctor) {
			ctor(current);
		}
		*/

		spl_ptr_llist_push(to, &current->data);
		current = next;
	}

}