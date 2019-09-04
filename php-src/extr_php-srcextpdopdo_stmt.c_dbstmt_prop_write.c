#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  dbh; } ;
typedef  TYPE_1__ pdo_stmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_raise_impl_error (int /*<<< orphan*/ ,TYPE_1__*,char*,char*) ; 
 TYPE_1__* php_pdo_stmt_fetch_object (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zend_std_write_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static zval *dbstmt_prop_write(zend_object *object, zend_string *name, zval *value, void **cache_slot)
{
	pdo_stmt_t *stmt = php_pdo_stmt_fetch_object(object);

	if (strcmp(ZSTR_VAL(name), "queryString") == 0) {
		pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "property queryString is read only");
		return value;
	} else {
		return zend_std_write_property(object, name, value, cache_slot);
	}
}