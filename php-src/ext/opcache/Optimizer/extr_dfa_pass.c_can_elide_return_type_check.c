#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_ssa_var_info ;
struct TYPE_10__ {size_t op1_use; size_t op1_def; } ;
typedef  TYPE_2__ zend_ssa_op ;
struct TYPE_11__ {TYPE_1__* var_info; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_12__ {TYPE_5__* arg_info; } ;
typedef  TYPE_4__ zend_op_array ;
typedef  int zend_bool ;
struct TYPE_13__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ zend_arg_info ;

/* Variables and functions */
 int MAY_BE_ANY ; 
 int MAY_BE_CALLABLE ; 
 int MAY_BE_ITERABLE ; 
 int MAY_BE_REF ; 
 int MAY_BE_UNDEF ; 
 int ZEND_TYPE_FULL_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_HAS_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_instanceof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_bool can_elide_return_type_check(
		zend_op_array *op_array, zend_ssa *ssa, zend_ssa_op *ssa_op) {
	zend_arg_info *info = &op_array->arg_info[-1];
	zend_ssa_var_info *use_info = &ssa->var_info[ssa_op->op1_use];
	zend_ssa_var_info *def_info = &ssa->var_info[ssa_op->op1_def];

	/* TODO: It would be better to rewrite this without using def_info,
	 * which may not be an exact representation of the type. */
	if (use_info->type & MAY_BE_REF) {
		return 0;
	}

	/* A type is possible that is not in the allowed types */
	if ((use_info->type & (MAY_BE_ANY|MAY_BE_UNDEF)) & ~(def_info->type & MAY_BE_ANY)) {
		return 0;
	}

	/* These types are not represented exactly */
	if (ZEND_TYPE_FULL_MASK(info->type) & (MAY_BE_CALLABLE|MAY_BE_ITERABLE)) {
		return 0;
	}

	if (ZEND_TYPE_HAS_CLASS(info->type)) {
		if (!use_info->ce || !def_info->ce || !safe_instanceof(use_info->ce, def_info->ce)) {
			return 0;
		}
	}

	return 1;
}