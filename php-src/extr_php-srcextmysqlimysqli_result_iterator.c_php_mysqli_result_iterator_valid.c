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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  current_row; } ;
typedef  TYPE_1__ php_mysqli_result_iterator ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 int SUCCESS ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_mysqli_result_iterator_valid(zend_object_iterator *iter)
{
	php_mysqli_result_iterator *iterator = (php_mysqli_result_iterator*) iter;

	return Z_TYPE(iterator->current_row) == IS_ARRAY ? SUCCESS : FAILURE;
}