#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int arg_count; struct TYPE_5__* arguments; } ;
typedef  TYPE_1__ php_shutdown_function_entry ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (TYPE_1__*) ; 

void user_shutdown_function_dtor(zval *zv) /* {{{ */
{
	int i;
	php_shutdown_function_entry *shutdown_function_entry = Z_PTR_P(zv);

	for (i = 0; i < shutdown_function_entry->arg_count; i++) {
		zval_ptr_dtor(&shutdown_function_entry->arguments[i]);
	}
	efree(shutdown_function_entry->arguments);
	efree(shutdown_function_entry);
}