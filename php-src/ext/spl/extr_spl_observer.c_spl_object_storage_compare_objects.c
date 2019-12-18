#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {scalar_t__ ce; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  compare_func_t ;
struct TYPE_4__ {int /*<<< orphan*/  storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_COMPARE_OBJECTS_FALLBACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_SPLOBJSTORAGE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ spl_ce_SplObjectStorage ; 
 scalar_t__ spl_object_storage_compare_info ; 
 int zend_hash_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spl_object_storage_compare_objects(zval *o1, zval *o2) /* {{{ */
{
	zend_object *zo1;
	zend_object *zo2;

	ZEND_COMPARE_OBJECTS_FALLBACK(o1, o2);

	zo1 = (zend_object *)Z_OBJ_P(o1);
	zo2 = (zend_object *)Z_OBJ_P(o2);

	if (zo1->ce != spl_ce_SplObjectStorage || zo2->ce != spl_ce_SplObjectStorage) {
		return 1;
	}

	return zend_hash_compare(&(Z_SPLOBJSTORAGE_P(o1))->storage, &(Z_SPLOBJSTORAGE_P(o2))->storage, (compare_func_t)spl_object_storage_compare_info, 0);
}