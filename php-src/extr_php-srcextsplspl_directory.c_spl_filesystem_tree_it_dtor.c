#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  current; TYPE_1__ intern; } ;
typedef  TYPE_2__ spl_filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_filesystem_tree_it_dtor(zend_object_iterator *iter)
{
	spl_filesystem_iterator *iterator = (spl_filesystem_iterator *)iter;

	if (!Z_ISUNDEF(iterator->intern.data)) {
		zval *object = &iterator->intern.data;
		zval_ptr_dtor(object);
	} else {
		if (!Z_ISUNDEF(iterator->current)) {
			zval_ptr_dtor(&iterator->current);
			ZVAL_UNDEF(&iterator->current);
		}
	}
}