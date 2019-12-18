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
struct TYPE_2__ {int module_number; } ;
typedef  TYPE_1__ zend_ini_entry ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zend_remove_ini_entries(zval *el, void *arg) /* {{{ */
{
	zend_ini_entry *ini_entry = (zend_ini_entry *)Z_PTR_P(el);
	int module_number = *(int *)arg;

	return ini_entry->module_number == module_number;
}