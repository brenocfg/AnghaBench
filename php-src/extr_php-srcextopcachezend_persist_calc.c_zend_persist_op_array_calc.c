#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_6__ {scalar_t__ corrupted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ARENA_SIZE (int) ; 
 int /*<<< orphan*/  ADD_SIZE (int) ; 
 TYPE_4__* ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_persistent_script ; 
 int /*<<< orphan*/  zend_persist_op_array_calc_ex (TYPE_1__*) ; 

__attribute__((used)) static void zend_persist_op_array_calc(zval *zv)
{
	zend_op_array *op_array = Z_PTR_P(zv);

	ZEND_ASSERT(op_array->type == ZEND_USER_FUNCTION);
	ADD_SIZE(sizeof(zend_op_array));
	zend_persist_op_array_calc_ex(Z_PTR_P(zv));
	if (ZCG(current_persistent_script)->corrupted) {
		ADD_ARENA_SIZE(sizeof(void*));
	}
}