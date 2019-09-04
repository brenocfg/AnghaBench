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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ it; } ;
struct TYPE_6__ {TYPE_2__ intern; } ;
typedef  TYPE_3__ spl_heap_it ;

/* Variables and functions */
 int /*<<< orphan*/  zend_user_it_invalidate_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_heap_it_dtor(zend_object_iterator *iter) /* {{{ */
{
	spl_heap_it *iterator = (spl_heap_it *)iter;

	zend_user_it_invalidate_current(iter);
	zval_ptr_dtor(&iterator->intern.it.data);
}