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
struct TYPE_5__ {int /*<<< orphan*/  zo; int /*<<< orphan*/  db_obj_zval; int /*<<< orphan*/  stmt; TYPE_1__* db_obj; scalar_t__ initialised; int /*<<< orphan*/ * bound_params; } ;
typedef  TYPE_2__ php_sqlite3_stmt ;
struct TYPE_4__ {int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_HASHTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ php_sqlite3_compare_stmt_free ; 
 TYPE_2__* php_sqlite3_stmt_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_llist_del_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int (*) (void*,void*)) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sqlite3_stmt_object_free_storage(zend_object *object) /* {{{ */
{
	php_sqlite3_stmt *intern = php_sqlite3_stmt_from_obj(object);

	if (!intern) {
		return;
	}

	if (intern->bound_params) {
		zend_hash_destroy(intern->bound_params);
		FREE_HASHTABLE(intern->bound_params);
		intern->bound_params = NULL;
	}

	if (intern->initialised) {
		zend_llist_del_element(&(intern->db_obj->free_list), intern->stmt,
			(int (*)(void *, void *)) php_sqlite3_compare_stmt_free);
	}

	if (!Z_ISUNDEF(intern->db_obj_zval)) {
		zval_ptr_dtor(&intern->db_obj_zval);
	}

	zend_object_std_dtor(&intern->zo);
}