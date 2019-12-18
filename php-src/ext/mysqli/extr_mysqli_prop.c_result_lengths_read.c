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
typedef  size_t zend_ulong ;
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  MYSQL_RES ;
typedef  TYPE_2__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLI_STATUS_VALID ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_index_long (int /*<<< orphan*/ *,size_t,size_t const) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 size_t* mysql_fetch_lengths (int /*<<< orphan*/ *) ; 
 size_t mysql_num_fields (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zval *result_lengths_read(mysqli_object *obj, zval *retval)
{
	MYSQL_RES *p;
#if defined(MYSQLI_USE_MYSQLND)
	const size_t *ret;
#else
	const zend_ulong *ret;
#endif
	uint32_t field_count;

	CHECK_STATUS(MYSQLI_STATUS_VALID);
	p = (MYSQL_RES *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;
	field_count = mysql_num_fields(p);
	if (!p || !field_count || !(ret = mysql_fetch_lengths(p))) {
		ZVAL_NULL(retval);
	} else {
		zend_ulong i;

		array_init(retval);

		for (i = 0; i < field_count; i++) {
			add_index_long(retval, i, ret[i]);
		}
	}
	return retval;
}