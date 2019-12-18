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
typedef  int /*<<< orphan*/  zend_object ;
typedef  scalar_t__ zend_long ;
struct TYPE_6__ {scalar_t__ column_count; TYPE_1__* columns; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_2__* stmt; } ;
typedef  TYPE_3__ pdo_row_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_value (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int i_zend_is_true (int /*<<< orphan*/ *) ; 
 scalar_t__ is_numeric_string_ex (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int row_dim_exists(zend_object *object, zval *member, int check_empty)
{
	pdo_row_t *row = (pdo_row_t *)object;
	pdo_stmt_t *stmt = row->stmt;
	int colno = -1;
	zend_long lval;

	if (stmt) {
		if (Z_TYPE_P(member) == IS_LONG) {
			return Z_LVAL_P(member) >= 0 && Z_LVAL_P(member) < stmt->column_count;
		} else if (Z_TYPE_P(member) == IS_STRING) {
			if (is_numeric_string_ex(Z_STRVAL_P(member), Z_STRLEN_P(member), &lval, NULL, 0, NULL) == IS_LONG)	{
				return lval >=0 && lval < stmt->column_count;
			}
		} else {
			if (!try_convert_to_string(member)) {
				return 0;
			}
		}

		/* TODO: replace this with a hash of available column names to column
		 * numbers */
		for (colno = 0; colno < stmt->column_count; colno++) {
			if (ZSTR_LEN(stmt->columns[colno].name) == Z_STRLEN_P(member) &&
			    strncmp(ZSTR_VAL(stmt->columns[colno].name), Z_STRVAL_P(member), Z_STRLEN_P(member)) == 0) {
					int res;
					zval val;

					fetch_value(stmt, &val, colno, NULL);
					res = check_empty ? i_zend_is_true(&val) : Z_TYPE(val) != IS_NULL;
					zval_ptr_dtor_nogc(&val);

					return res;
			}
		}
	}

	return 0;
}