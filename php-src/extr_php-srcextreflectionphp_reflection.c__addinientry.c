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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int module_number; int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ zend_ini_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_symtable_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _addinientry(zend_ini_entry *ini_entry, zval *retval, int number)
{
	if (number == ini_entry->module_number) {
		zval zv;
		if (ini_entry->value) {
			ZVAL_STR_COPY(&zv, ini_entry->value);
		} else {
			ZVAL_NULL(&zv);
		}
		zend_symtable_update(Z_ARRVAL_P(retval), ini_entry->name, &zv);
	}
}