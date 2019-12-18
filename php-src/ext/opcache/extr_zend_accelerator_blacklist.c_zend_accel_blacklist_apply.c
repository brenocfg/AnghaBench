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
struct TYPE_3__ {int pos; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ zend_blacklist ;
typedef  int /*<<< orphan*/  (* blacklist_apply_func_arg_t ) (int /*<<< orphan*/ *,void*) ;

/* Variables and functions */

void zend_accel_blacklist_apply(zend_blacklist *blacklist, blacklist_apply_func_arg_t func, void *argument)
{
	int i;

	for (i = 0; i < blacklist->pos; i++) {
		func(&blacklist->entries[i], argument);
	}
}