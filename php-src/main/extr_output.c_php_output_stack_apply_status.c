#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_output_handler ;

/* Variables and functions */
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_output_handler_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_output_stack_apply_status(void *h, void *z)
{
	php_output_handler *handler = *(php_output_handler **) h;
	zval arr, *array = (zval *) z;

	add_next_index_zval(array, php_output_handler_status(handler, &arr));

	return 0;
}