#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_11__ {TYPE_1__* ce; } ;
typedef  TYPE_3__ zend_object ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_12__ {TYPE_2__* dbh; int /*<<< orphan*/  database_object_handle; } ;
typedef  TYPE_4__ pdo_stmt_t ;
struct TYPE_10__ {int /*<<< orphan*/ ** cls_methods; } ;
struct TYPE_9__ {int /*<<< orphan*/  function_table; } ;

/* Variables and functions */
 size_t PDO_DBH_DRIVER_METHOD_KIND_STMT ; 
 int /*<<< orphan*/  Z_PDO_OBJECT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_hash_methods (int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* php_pdo_stmt_fetch_object (TYPE_3__*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_method (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_function *dbstmt_method_get(zend_object **object_pp, zend_string *method_name, const zval *key)
{
	zend_function *fbc = NULL;
	zend_string *lc_method_name;
	zend_object *object = *object_pp;

	lc_method_name = zend_string_tolower(method_name);

	if ((fbc = zend_hash_find_ptr(&object->ce->function_table, lc_method_name)) == NULL) {
		pdo_stmt_t *stmt = php_pdo_stmt_fetch_object(object);
		/* instance not created by PDO object */
		if (!stmt->dbh) {
			goto out;
		}
		/* not a pre-defined method, nor a user-defined method; check
		 * the driver specific methods */
		if (!stmt->dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_STMT]) {
			if (!pdo_hash_methods(Z_PDO_OBJECT_P(&stmt->database_object_handle),
				PDO_DBH_DRIVER_METHOD_KIND_STMT)
				|| !stmt->dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_STMT]) {
				goto out;
			}
		}

		if ((fbc = zend_hash_find_ptr(stmt->dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_STMT], lc_method_name)) == NULL) {
			goto out;
		}
		/* got it */
	}

out:
	zend_string_release_ex(lc_method_name, 0);
	if (!fbc) {
		fbc = zend_std_get_method(object_pp, method_name, key);
	}
	return fbc;
}