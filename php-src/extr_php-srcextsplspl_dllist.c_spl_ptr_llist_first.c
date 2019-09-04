#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ spl_ptr_llist_element ;
struct TYPE_5__ {TYPE_1__* head; } ;
typedef  TYPE_2__ spl_ptr_llist ;

/* Variables and functions */

__attribute__((used)) static zval *spl_ptr_llist_first(spl_ptr_llist *llist) /* {{{ */
{
	spl_ptr_llist_element *head = llist->head;

	if (head == NULL) {
		return NULL;
	} else {
		return &head->data;
	}
}