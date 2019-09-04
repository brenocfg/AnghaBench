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
struct TYPE_4__ {int /*<<< orphan*/  constructor; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int /*<<< orphan*/  pdo_dbh_t ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/  Z_ISUNDEF_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ object_init_ex (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdo_raise_impl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static zval *pdo_stmt_instantiate(pdo_dbh_t *dbh, zval *object, zend_class_entry *dbstmt_ce, zval *ctor_args) /* {{{ */
{
	if (!Z_ISUNDEF_P(ctor_args)) {
		if (Z_TYPE_P(ctor_args) != IS_ARRAY) {
			pdo_raise_impl_error(dbh, NULL, "HY000", "constructor arguments must be passed as an array");
			return NULL;
		}
		if (!dbstmt_ce->constructor) {
			pdo_raise_impl_error(dbh, NULL, "HY000", "user-supplied statement does not accept constructor arguments");
			return NULL;
		}
	}

	if (UNEXPECTED(object_init_ex(object, dbstmt_ce) != SUCCESS)) {
		return NULL;
	}

	return object;
}