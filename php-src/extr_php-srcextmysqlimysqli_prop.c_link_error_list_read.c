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
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mysql; } ;
typedef  TYPE_2__ MY_MYSQL ;
typedef  TYPE_3__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLI_STATUS_VALID ; 
 int /*<<< orphan*/  ZVAL_EMPTY_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_long_ex (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  add_assoc_string_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_sqlstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *link_error_list_read(mysqli_object *obj, zval *retval)
{
	MY_MYSQL *mysql;

	CHECK_STATUS(MYSQLI_STATUS_VALID);

 	mysql = (MY_MYSQL *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;

	if (mysql) {
		array_init(retval);
#if defined(MYSQLI_USE_MYSQLND)
		if (1) {
			MYSQLND_ERROR_LIST_ELEMENT * message;
			zend_llist_position pos;
			for (message = (MYSQLND_ERROR_LIST_ELEMENT *) zend_llist_get_first_ex(&mysql->mysql->data->error_info->error_list, &pos);
				 message;
				 message = (MYSQLND_ERROR_LIST_ELEMENT *) zend_llist_get_next_ex(&mysql->mysql->data->error_info->error_list, &pos))
			{
				zval single_error;
				array_init(&single_error);
				add_assoc_long_ex(&single_error, "errno", sizeof("errno") - 1, message->error_no);
				add_assoc_string_ex(&single_error, "sqlstate", sizeof("sqlstate") - 1, message->sqlstate);
				add_assoc_string_ex(&single_error, "error", sizeof("error") - 1, message->error);
				add_next_index_zval(retval, &single_error);
			}
		}
#else
		if (mysql_errno(mysql->mysql)) {
			zval single_error;
			array_init(&single_error);
			add_assoc_long_ex(&single_error, "errno", sizeof("errno") - 1, mysql_errno(mysql->mysql));
			add_assoc_string_ex(&single_error, "sqlstate", sizeof("sqlstate") - 1, mysql_sqlstate(mysql->mysql));
			add_assoc_string_ex(&single_error, "error", sizeof("error") - 1, mysql_error(mysql->mysql));
			add_next_index_zval(retval, &single_error);
		}
#endif
	} else {
		ZVAL_EMPTY_ARRAY(retval);
	}

	return retval;
}