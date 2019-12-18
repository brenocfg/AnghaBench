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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  enum_func_status ;
struct TYPE_5__ {unsigned int param_count; int /*<<< orphan*/  error_info; TYPE_1__* param_bind; } ;
struct TYPE_4__ {int type; int flags; int /*<<< orphan*/  zv; } ;
typedef  TYPE_2__ MYSQLND_STMT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ IS_DOUBLE ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_STRING ; 
 int MYSQLND_PARAM_BIND_BLOB_USED ; 
#define  MYSQL_TYPE_DOUBLE 132 
#define  MYSQL_TYPE_LONG 131 
#define  MYSQL_TYPE_LONGLONG 130 
#define  MYSQL_TYPE_LONG_BLOB 129 
#define  MYSQL_TYPE_VAR_STRING 128 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_OOM_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ISREF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISREF_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_long_ex (int /*<<< orphan*/ *) ; 
 scalar_t__ mysqlnd_stmt_copy_it (int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_execute_calculate_param_values_size(MYSQLND_STMT_DATA * stmt, zval ** copies_param, size_t * data_size)
{
	unsigned int i;
	DBG_ENTER("mysqlnd_stmt_execute_calculate_param_values_size");
	for (i = 0; i < stmt->param_count; i++) {
		unsigned short is_longlong = 0;
		unsigned int j;
		zval *bind_var, *the_var = &stmt->param_bind[i].zv;

		bind_var = the_var;
		ZVAL_DEREF(the_var);
		if ((stmt->param_bind[i].type != MYSQL_TYPE_LONG_BLOB && Z_TYPE_P(the_var) == IS_NULL)) {
			continue;
		}

		if (Z_ISREF_P(bind_var)) {
			for (j = i + 1; j < stmt->param_count; j++) {
				if (Z_ISREF(stmt->param_bind[j].zv) && Z_REFVAL(stmt->param_bind[j].zv) == the_var) {
					/* Double binding of the same zval, make a copy */
					if (!*copies_param || Z_ISUNDEF((*copies_param)[i])) {
						if (PASS != mysqlnd_stmt_copy_it(copies_param, the_var, stmt->param_count, i)) {
							SET_OOM_ERROR(stmt->error_info);
							goto end;
						}
					}
					break;
				}
			}
		}

		switch (stmt->param_bind[i].type) {
			case MYSQL_TYPE_DOUBLE:
				*data_size += 8;
				if (Z_TYPE_P(the_var) != IS_DOUBLE) {
					if (!*copies_param || Z_ISUNDEF((*copies_param)[i])) {
						if (PASS != mysqlnd_stmt_copy_it(copies_param, the_var, stmt->param_count, i)) {
							SET_OOM_ERROR(stmt->error_info);
							goto end;
						}
					}
				}
				break;
			case MYSQL_TYPE_LONGLONG:
				is_longlong = 4;
				/* fall-through */
			case MYSQL_TYPE_LONG:
				{
					zval *tmp_data = (*copies_param && !Z_ISUNDEF((*copies_param)[i]))? &(*copies_param)[i]: the_var;
					if (Z_TYPE_P(tmp_data) == IS_STRING) {
						goto use_string;
					}
					convert_to_long_ex(tmp_data);
				}
				*data_size += 4 + is_longlong;
				break;
			case MYSQL_TYPE_LONG_BLOB:
				if (!(stmt->param_bind[i].flags & MYSQLND_PARAM_BIND_BLOB_USED)) {
					/*
					  User hasn't sent anything, we will send empty string.
					  Empty string has length of 0, encoded in 1 byte. No real
					  data will follows after it.
					*/
					(*data_size)++;
				}
				break;
			case MYSQL_TYPE_VAR_STRING:
use_string:
				*data_size += 8; /* max 8 bytes for size */
				if (Z_TYPE_P(the_var) != IS_STRING) {
					if (!*copies_param || Z_ISUNDEF((*copies_param)[i])) {
						if (PASS != mysqlnd_stmt_copy_it(copies_param, the_var, stmt->param_count, i)) {
							SET_OOM_ERROR(stmt->error_info);
							goto end;
						}
					}
					the_var = &((*copies_param)[i]);
				}

				if (!try_convert_to_string(the_var)) {
					goto end;
				}
				*data_size += Z_STRLEN_P(the_var);
				break;
		}
	}
	DBG_RETURN(PASS);
end:
	DBG_RETURN(FAIL);
}