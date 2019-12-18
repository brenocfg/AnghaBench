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
struct TYPE_2__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ spl_pqueue_elem ;

/* Variables and functions */
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_ptr_heap_pqueue_elem_dtor(void *elem) { /* {{{ */
	spl_pqueue_elem *pq_elem = elem;
	zval_ptr_dtor(&pq_elem->data);
	zval_ptr_dtor(&pq_elem->priority);
}