#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_6__ {TYPE_1__* inner; } ;
typedef  TYPE_2__ pdo_dbh_object_t ;
struct TYPE_5__ {int /*<<< orphan*/ * cls_methods; } ;

/* Variables and functions */
 size_t PDO_DBH_DRIVER_METHOD_KIND_DBH ; 
 int /*<<< orphan*/  pdo_hash_methods (TYPE_2__*,size_t) ; 
 TYPE_2__* php_pdo_dbh_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_method (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_function *dbh_method_get(zend_object **object, zend_string *method_name, const zval *key)
{
	zend_function *fbc = NULL;
	pdo_dbh_object_t *dbh_obj = php_pdo_dbh_fetch_object(*object);
	zend_string *lc_method_name;

	if ((fbc = zend_std_get_method(object, method_name, key)) == NULL) {
		/* not a pre-defined method, nor a user-defined method; check
		 * the driver specific methods */
		if (!dbh_obj->inner->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH]) {
			if (!pdo_hash_methods(dbh_obj,
				PDO_DBH_DRIVER_METHOD_KIND_DBH)
				|| !dbh_obj->inner->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH]) {
				goto out;
			}
		}

		lc_method_name = zend_string_tolower(method_name);
		fbc = zend_hash_find_ptr(dbh_obj->inner->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH], lc_method_name);
		zend_string_release_ex(lc_method_name, 0);
	}

out:
	return fbc;
}