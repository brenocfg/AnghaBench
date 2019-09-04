#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {int /*<<< orphan*/  zo; int /*<<< orphan*/  stmt_obj_zval; TYPE_1__* stmt_obj; } ;
typedef  TYPE_2__ php_sqlite3_result ;
struct TYPE_4__ {int /*<<< orphan*/  stmt; scalar_t__ initialised; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ISNULL (int /*<<< orphan*/ ) ; 
 TYPE_2__* php_sqlite3_result_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sqlite3_result_object_free_storage(zend_object *object) /* {{{ */
{
	php_sqlite3_result *intern = php_sqlite3_result_from_obj(object);

	if (!intern) {
		return;
	}

	if (!Z_ISNULL(intern->stmt_obj_zval)) {
		if (intern->stmt_obj && intern->stmt_obj->initialised) {
			sqlite3_reset(intern->stmt_obj->stmt);
		}

		zval_ptr_dtor(&intern->stmt_obj_zval);
	}

	zend_object_std_dtor(&intern->zo);
}