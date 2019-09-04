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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ php_output_handler ;

/* Variables and functions */
 int /*<<< orphan*/  add_next_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_output_stack_apply_list(void *h, void *z)
{
	php_output_handler *handler = *(php_output_handler **) h;
	zval *array = (zval *) z;

	add_next_index_str(array, zend_string_copy(handler->name));
	return 0;
}