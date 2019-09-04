#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int arg_count; int /*<<< orphan*/ * arguments; } ;
typedef  TYPE_1__ user_tick_function_entry ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void user_tick_function_dtor(user_tick_function_entry *tick_function_entry) /* {{{ */
{
	int i;

	for (i = 0; i < tick_function_entry->arg_count; i++) {
		zval_ptr_dtor(&tick_function_entry->arguments[i]);
	}
	efree(tick_function_entry->arguments);
}