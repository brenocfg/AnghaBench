#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ spl_pqueue_elem ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ISUNDEF_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_ptr_heap_pqueue_elem_dtor(zval *zv) { /* {{{ */
	if (!Z_ISUNDEF_P(zv)) {
		spl_pqueue_elem *elem = Z_PTR_P(zv);
		zval_ptr_dtor(&elem->data);
		zval_ptr_dtor(&elem->priority);
		efree(elem);
	}
}