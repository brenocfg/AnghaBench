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
typedef  int /*<<< orphan*/  const zval ;
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_5__ {unsigned int param_count; TYPE_1__* param_bind; } ;
struct TYPE_4__ {short type; int /*<<< orphan*/  const zv; } ;
typedef  TYPE_2__ MYSQLND_STMT_DATA ;

/* Variables and functions */
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 short MYSQL_TYPE_LONG ; 
 short MYSQL_TYPE_LONGLONG ; 
 short MYSQL_TYPE_VAR_STRING ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Z_ISNULL_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/  const) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  int2store (int /*<<< orphan*/ *,short) ; 

__attribute__((used)) static void
mysqlnd_stmt_execute_store_types(MYSQLND_STMT_DATA * stmt, zval * copies, zend_uchar ** p)
{
	unsigned int i;
	for (i = 0; i < stmt->param_count; i++) {
		short current_type = stmt->param_bind[i].type;
		zval *parameter = &stmt->param_bind[i].zv;
		/* our types are not unsigned */
#if SIZEOF_ZEND_LONG==8
		if (current_type == MYSQL_TYPE_LONG) {
			current_type = MYSQL_TYPE_LONGLONG;
		}
#endif
		ZVAL_DEREF(parameter);
		if (!Z_ISNULL_P(parameter) && (current_type == MYSQL_TYPE_LONG || current_type == MYSQL_TYPE_LONGLONG)) {
			/*
			  if it doesn't fit in a long send it as a string.
			  Check bug #52891 : Wrong data inserted with mysqli/mysqlnd when using bind_param, value > LONG_MAX
			*/
			if (Z_TYPE_P(parameter) != IS_LONG) {
				const zval *tmp_data = (copies && !Z_ISUNDEF(copies[i]))? &copies[i] : parameter;
				/*
				  In case of IS_LONG we do nothing, it is ok, in case of string, we just need to set current_type.
				  The actual transformation has been performed several dozens line above.
				*/
				if (Z_TYPE_P(tmp_data) == IS_STRING) {
					current_type = MYSQL_TYPE_VAR_STRING;
					/*
					  don't change stmt->param_bind[i].type to MYSQL_TYPE_VAR_STRING
					  we force convert_to_long_ex in all cases, thus the type will be right in the next switch.
					  if the type is however not long, then we will do a goto in the next switch.
					  We want to preserve the original bind type given by the user. Thus, we do these hacks.
					*/
				}
			}
		}
		int2store(*p, current_type);
		*p+= 2;
	}
}