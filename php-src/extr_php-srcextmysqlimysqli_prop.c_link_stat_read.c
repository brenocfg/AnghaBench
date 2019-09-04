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
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mysql_stat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *link_stat_read(mysqli_object *obj, zval *retval)
{
	MY_MYSQL *mysql;

	ZVAL_NULL(retval);

#if defined(MYSQLI_USE_MYSQLND)
	CHECK_STATUS(MYSQLI_STATUS_INITIALIZED);
#else
	CHECK_STATUS(MYSQLI_STATUS_VALID);
#endif

 	mysql = (MY_MYSQL *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;

	if (mysql) {
#if defined(MYSQLI_USE_MYSQLND)
		zend_string * stat_msg;
		if (mysqlnd_stat(mysql->mysql, &stat_msg) == PASS) {
			ZVAL_STR(retval, stat_msg);
		}
#else
		char * stat_msg;
		if ((stat_msg = (char *)mysql_stat(mysql->mysql))) {
			ZVAL_STRING(retval, stat_msg);
		}
#endif
	}
	return retval;
}