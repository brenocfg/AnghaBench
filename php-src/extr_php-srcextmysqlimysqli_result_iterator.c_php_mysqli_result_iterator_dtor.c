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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  current_row; TYPE_1__ intern; } ;
typedef  TYPE_2__ php_mysqli_result_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_mysqli_result_iterator_dtor(zend_object_iterator *iter)
{
	php_mysqli_result_iterator *iterator = (php_mysqli_result_iterator*)iter;

	/* cleanup handled in sxe_object_dtor as we don't always have an iterator wrapper */
	zval_ptr_dtor(&iterator->intern.data);
	zval_ptr_dtor(&iterator->current_row);
}