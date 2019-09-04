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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  row_num; } ;
typedef  TYPE_1__ php_mysqli_result_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_mysqli_result_iterator_current_key(zend_object_iterator *iter, zval *key)
{
	php_mysqli_result_iterator *iterator = (php_mysqli_result_iterator*) iter;

	ZVAL_LONG(key, iterator->row_num);
}