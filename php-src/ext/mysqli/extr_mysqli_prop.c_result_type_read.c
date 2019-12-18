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
struct TYPE_4__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  MYSQL_RES ;
typedef  TYPE_2__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLI_STATUS_VALID ; 
 int /*<<< orphan*/  MYSQLI_STORE_RESULT ; 
 int /*<<< orphan*/  MYSQLI_USE_RESULT ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 scalar_t__ mysqli_result_is_unbuffered (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zval *result_type_read(mysqli_object *obj, zval *retval)
{
	MYSQL_RES *p;

	CHECK_STATUS(MYSQLI_STATUS_VALID);
 	p = (MYSQL_RES *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;

	if (!p) {
		ZVAL_NULL(retval);
	} else {
		ZVAL_LONG(retval, mysqli_result_is_unbuffered(p) ? MYSQLI_USE_RESULT:MYSQLI_STORE_RESULT);
	}
	return retval;
}