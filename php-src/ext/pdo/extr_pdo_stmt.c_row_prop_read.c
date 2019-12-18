#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  scalar_t__ zend_long ;
struct TYPE_6__ {scalar_t__ column_count; int /*<<< orphan*/  std; TYPE_1__* columns; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_2__* stmt; } ;
typedef  TYPE_3__ pdo_row_t ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ IS_LONG ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_value (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_numeric_string_ex (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * zend_std_read_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zval *row_prop_read(zend_object *object, zend_string *name, int type, void **cache_slot, zval *rv)
{
	pdo_row_t *row = (pdo_row_t *)object;
	pdo_stmt_t *stmt = row->stmt;
	int colno = -1;
	zend_long lval;

	ZVAL_NULL(rv);
	if (stmt) {
		if (is_numeric_string_ex(ZSTR_VAL(name), ZSTR_LEN(name), &lval, NULL, 0, NULL) == IS_LONG)	{
			if (lval >= 0 && lval < stmt->column_count) {
				fetch_value(stmt, rv, lval, NULL);
			}
		} else {
			/* TODO: replace this with a hash of available column names to column
			 * numbers */
			for (colno = 0; colno < stmt->column_count; colno++) {
				if (ZSTR_LEN(stmt->columns[colno].name) == ZSTR_LEN(name) &&
				    strncmp(ZSTR_VAL(stmt->columns[colno].name), ZSTR_VAL(name), ZSTR_LEN(name)) == 0) {
					fetch_value(stmt, rv, colno, NULL);
					return rv;
				}
			}
			if (strcmp(ZSTR_VAL(name), "queryString") == 0) {
				//zval_ptr_dtor(rv);
				return zend_std_read_property(&stmt->std, name, type, cache_slot, rv);
			}
		}
	}

	return rv;
}