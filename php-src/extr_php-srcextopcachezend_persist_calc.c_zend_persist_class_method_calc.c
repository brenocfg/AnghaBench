#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {scalar_t__ type; int fn_flags; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_internal_function ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ARENA_SIZE (int) ; 
 int /*<<< orphan*/  ADD_SIZE_EX (int) ; 
 int /*<<< orphan*/  ZCG (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_ARENA_ALLOCATED ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_immutable_class ; 
 int /*<<< orphan*/  zend_persist_op_array_calc_ex (TYPE_1__*) ; 
 TYPE_1__* zend_shared_alloc_get_xlat_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_shared_alloc_register_xlat_entry (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void zend_persist_class_method_calc(zval *zv)
{
	zend_op_array *op_array = Z_PTR_P(zv);
	zend_op_array *old_op_array;

	if (op_array->type != ZEND_USER_FUNCTION) {
		ZEND_ASSERT(op_array->type == ZEND_INTERNAL_FUNCTION);
		if (op_array->fn_flags & ZEND_ACC_ARENA_ALLOCATED) {
			old_op_array = zend_shared_alloc_get_xlat_entry(op_array);
			if (!old_op_array) {
				ADD_SIZE_EX(sizeof(zend_internal_function));
				zend_shared_alloc_register_xlat_entry(op_array, Z_PTR_P(zv));
			}
		}
		return;
	}

	old_op_array = zend_shared_alloc_get_xlat_entry(op_array);
	if (!old_op_array) {
		ADD_SIZE_EX(sizeof(zend_op_array));
		zend_persist_op_array_calc_ex(Z_PTR_P(zv));
		zend_shared_alloc_register_xlat_entry(op_array, Z_PTR_P(zv));
		if (!ZCG(is_immutable_class)) {
			ADD_ARENA_SIZE(sizeof(void*));
		}
	}
}