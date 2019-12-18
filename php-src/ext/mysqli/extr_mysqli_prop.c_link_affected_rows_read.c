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
typedef  int zend_long ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
typedef  scalar_t__ my_ulonglong ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mysql; } ;
typedef  TYPE_2__ MY_MYSQL ;
typedef  TYPE_3__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLI_LLU_SPEC ; 
 int /*<<< orphan*/  MYSQLI_STATUS_INITIALIZED ; 
 int /*<<< orphan*/  MYSQLI_STATUS_VALID ; 
 scalar_t__ ZEND_LONG_MAX ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_affected_rows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strpprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static zval *link_affected_rows_read(mysqli_object *obj, zval *retval)
{
	MY_MYSQL *mysql;
	my_ulonglong rc;

	CHECK_STATUS(MYSQLI_STATUS_INITIALIZED);

 	mysql = (MY_MYSQL *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;

	if (!mysql) {
		ZVAL_NULL(retval);
	} else {
		CHECK_STATUS(MYSQLI_STATUS_VALID);

		rc = mysql_affected_rows(mysql->mysql);

		if (rc == (my_ulonglong) -1) {
			ZVAL_LONG(retval, -1);
			return retval;
		}

		if (rc < ZEND_LONG_MAX) {
			ZVAL_LONG(retval, (zend_long) rc);
		} else {
			ZVAL_NEW_STR(retval, strpprintf(0, MYSQLI_LLU_SPEC, rc));
		}
	}
	return retval;
}