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
struct TYPE_5__ {unsigned int param_count; int send_types_to_server; int /*<<< orphan*/  error_info; TYPE_1__* param_bind; } ;
struct TYPE_4__ {short type; int /*<<< orphan*/  zv; } ;
typedef  TYPE_2__ MYSQLND_STMT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ IS_LONG ; 
 short const MYSQL_TYPE_LONG ; 
 short const MYSQL_TYPE_LONGLONG ; 
 short const MYSQL_TYPE_TINY ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_OOM_ERROR (int /*<<< orphan*/ ) ; 
 double ZEND_LONG_MAX ; 
 double ZEND_LONG_MIN ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISNULL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string_ex (int /*<<< orphan*/ *) ; 
 scalar_t__ mysqlnd_stmt_copy_it (int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 double zval_get_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_execute_prepare_param_types(MYSQLND_STMT_DATA * stmt, zval ** copies_param, int * resend_types_next_time)
{
	unsigned int i;
	DBG_ENTER("mysqlnd_stmt_execute_prepare_param_types");
	for (i = 0; i < stmt->param_count; i++) {
		const short current_type = stmt->param_bind[i].type;
		zval *parameter = &stmt->param_bind[i].zv;

		ZVAL_DEREF(parameter);
		if (!Z_ISNULL_P(parameter) && (current_type == MYSQL_TYPE_LONG || current_type == MYSQL_TYPE_LONGLONG || current_type == MYSQL_TYPE_TINY)) {
			/* always copy the var, because we do many conversions */
			if (Z_TYPE_P(parameter) != IS_LONG &&
				PASS != mysqlnd_stmt_copy_it(copies_param, parameter, stmt->param_count, i))
			{
				SET_OOM_ERROR(stmt->error_info);
				goto end;
			}
			/*
			  if it doesn't fit in a long send it as a string.
			  Check bug #52891 : Wrong data inserted with mysqli/mysqlnd when using bind_param, value > LONG_MAX
			*/
			if (Z_TYPE_P(parameter) != IS_LONG) {
				zval *tmp_data = (*copies_param && !Z_ISUNDEF((*copies_param)[i]))? &(*copies_param)[i]: parameter;
				/*
				  Because converting to double and back to long can lead
				  to losing precision we need second variable. Conversion to double is to see if
				  value is too big for a long. As said, precision could be lost.
				*/
				double d = zval_get_double(tmp_data);

				/*
				  if it doesn't fit in a long send it as a string.
				  Check bug #52891 : Wrong data inserted with mysqli/mysqlnd when using bind_param, value > LONG_MAX
				  We do transformation here, which will be used later when sending types. The code later relies on this.
				*/
				if (d > ZEND_LONG_MAX || d < ZEND_LONG_MIN) {
					stmt->send_types_to_server = *resend_types_next_time = 1;
					convert_to_string_ex(tmp_data);
				} else {
					convert_to_long(tmp_data);
				}
			}
		}
	}
	DBG_RETURN(PASS);
end:
	DBG_RETURN(FAIL);
}