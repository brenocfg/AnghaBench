#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_18__ {int fn_flags; scalar_t__ arg_info; int /*<<< orphan*/  scope; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_3__ common; } ;
typedef  TYPE_4__ zend_function ;
struct TYPE_17__ {int type; } ;
struct TYPE_20__ {TYPE_2__ return_info; } ;
typedef  TYPE_5__ zend_func_info ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_21__ {TYPE_4__* callee_func; TYPE_13__* caller_init_opline; int /*<<< orphan*/  caller_op_array; } ;
typedef  TYPE_6__ zend_call_info ;
typedef  int uint32_t ;
struct TYPE_22__ {int (* info_func ) (TYPE_6__ const*,int /*<<< orphan*/  const*) ;int info; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ func_info_t ;
struct TYPE_16__ {char* function_name; } ;
struct TYPE_15__ {int /*<<< orphan*/  op2; } ;
struct TYPE_14__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_CONSTANT_EX (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_NULL ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_RCN ; 
 int MAY_BE_REF ; 
 scalar_t__ UNEXPECTED (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_GENERATOR ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 TYPE_5__* ZEND_FUNC_INFO (int /*<<< orphan*/ *) ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 TYPE_7__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_10__* func ; 
 int /*<<< orphan*/  func_info ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (TYPE_6__ const*,int /*<<< orphan*/  const*) ; 
 int zend_fetch_arg_info_type (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_optimizer_is_disabled_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t zend_get_func_info(const zend_call_info *call_info, const zend_ssa *ssa)
{
	uint32_t ret = 0;
	const zend_function *callee_func = call_info->callee_func;

	if (callee_func->type == ZEND_INTERNAL_FUNCTION) {
		zval *zv;
		zend_string *lcname = Z_STR_P(CRT_CONSTANT_EX(call_info->caller_op_array, call_info->caller_init_opline, call_info->caller_init_opline->op2));

		if (!call_info->callee_func->common.scope
				&& (zv = zend_hash_find_ex(&func_info, lcname, 1))) {
			func_info_t *info = Z_PTR_P(zv);
			if (UNEXPECTED(zend_optimizer_is_disabled_func(info->name, info->name_len))) {
				ret = MAY_BE_NULL;
			} else if (info->info_func) {
				ret = info->info_func(call_info, ssa);
			} else {
				ret = info->info;
			}
			return ret;
		}

		if (callee_func->common.fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
			zend_class_entry *ce; // TODO: Use the CE.
			ret = zend_fetch_arg_info_type(NULL, callee_func->common.arg_info - 1, &ce);
		} else {
#if 0
			fprintf(stderr, "Unknown internal function '%s'\n", func->common.function_name);
#endif
			ret = MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF
				| MAY_BE_RC1 | MAY_BE_RCN;
		}
		if (callee_func->common.fn_flags & ZEND_ACC_RETURN_REFERENCE) {
			ret |= MAY_BE_REF;
		}
	} else {
		// FIXME: the order of functions matters!!!
		zend_func_info *info = ZEND_FUNC_INFO((zend_op_array*)callee_func);
		if (info) {
			ret = info->return_info.type;
		}
		if (!ret) {
			ret = MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF
				| MAY_BE_RC1 | MAY_BE_RCN;
			/* For generators RETURN_REFERENCE refers to the yielded values. */
			if ((callee_func->common.fn_flags & ZEND_ACC_RETURN_REFERENCE)
					&& !(callee_func->common.fn_flags & ZEND_ACC_GENERATOR)) {
				ret |= MAY_BE_REF;
			}
		}
	}
	return ret;
}