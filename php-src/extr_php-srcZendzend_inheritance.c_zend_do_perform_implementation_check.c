#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ type; int fn_flags; scalar_t__ required_num_args; size_t num_args; TYPE_4__* arg_info; TYPE_1__* scope; } ;
struct TYPE_18__ {TYPE_2__ common; } ;
typedef  TYPE_3__ zend_function ;
typedef  int zend_bool ;
struct TYPE_19__ {scalar_t__ pass_by_reference; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ zend_arg_info ;
typedef  size_t uint32_t ;
struct TYPE_16__ {int ce_flags; } ;

/* Variables and functions */
#define  IS_ITERABLE 128 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_CTOR ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_INTERFACE ; 
 int ZEND_ACC_PRIVATE ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int ZEND_ACC_VARIADIC ; 
 scalar_t__ ZEND_TYPE_ALLOW_NULL (int /*<<< orphan*/ ) ; 
 int ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 int /*<<< orphan*/  zend_do_perform_arg_type_hint_check (TYPE_3__ const*,TYPE_4__*,TYPE_3__ const*,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_do_perform_type_hint_check (TYPE_3__ const*,TYPE_4__*,TYPE_3__ const*,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_iterable_compatibility_check (TYPE_4__*) ; 

__attribute__((used)) static zend_bool zend_do_perform_implementation_check(const zend_function *fe, const zend_function *proto) /* {{{ */
{
	uint32_t i, num_args;

	/* If it's a user function then arg_info == NULL means we don't have any parameters but
	 * we still need to do the arg number checks.  We are only willing to ignore this for internal
	 * functions because extensions don't always define arg_info.
	 */
	if (!proto->common.arg_info && proto->common.type != ZEND_USER_FUNCTION) {
		return 1;
	}

	/* Checks for constructors only if they are declared in an interface,
	 * or explicitly marked as abstract
	 */
	if ((fe->common.fn_flags & ZEND_ACC_CTOR)
		&& ((proto->common.scope->ce_flags & ZEND_ACC_INTERFACE) == 0
			&& (proto->common.fn_flags & ZEND_ACC_ABSTRACT) == 0)) {
		return 1;
	}

	/* If the prototype method is private do not enforce a signature */
	if (proto->common.fn_flags & ZEND_ACC_PRIVATE) {
		return 1;
	}

	/* check number of arguments */
	if (proto->common.required_num_args < fe->common.required_num_args
		|| proto->common.num_args > fe->common.num_args) {
		return 0;
	}

	/* by-ref constraints on return values are covariant */
	if ((proto->common.fn_flags & ZEND_ACC_RETURN_REFERENCE)
		&& !(fe->common.fn_flags & ZEND_ACC_RETURN_REFERENCE)) {
		return 0;
	}

	if ((proto->common.fn_flags & ZEND_ACC_VARIADIC)
		&& !(fe->common.fn_flags & ZEND_ACC_VARIADIC)) {
		return 0;
	}

	/* For variadic functions any additional (optional) arguments that were added must be
	 * checked against the signature of the variadic argument, so in this case we have to
	 * go through all the parameters of the function and not just those present in the
	 * prototype. */
	num_args = proto->common.num_args;
	if (proto->common.fn_flags & ZEND_ACC_VARIADIC) {
		num_args++;
        if (fe->common.num_args >= proto->common.num_args) {
			num_args = fe->common.num_args;
			if (fe->common.fn_flags & ZEND_ACC_VARIADIC) {
				num_args++;
			}
		}
	}

	for (i = 0; i < num_args; i++) {
		zend_arg_info *fe_arg_info = &fe->common.arg_info[i];

		zend_arg_info *proto_arg_info;
		if (i < proto->common.num_args) {
			proto_arg_info = &proto->common.arg_info[i];
		} else {
			proto_arg_info = &proto->common.arg_info[proto->common.num_args];
		}

		if (!zend_do_perform_arg_type_hint_check(fe, fe_arg_info, proto, proto_arg_info)) {
			switch (ZEND_TYPE_CODE(fe_arg_info->type)) {
				case IS_ITERABLE:
					if (!zend_iterable_compatibility_check(proto_arg_info)) {
						return 0;
					}
					break;

				default:
					return 0;
			}
		}

		// This introduces BC break described at https://bugs.php.net/bug.php?id=72119
		if (ZEND_TYPE_IS_SET(proto_arg_info->type) && ZEND_TYPE_ALLOW_NULL(proto_arg_info->type) && !ZEND_TYPE_ALLOW_NULL(fe_arg_info->type)) {
			/* incompatible nullability */
			return 0;
		}

		/* by-ref constraints on arguments are invariant */
		if (fe_arg_info->pass_by_reference != proto_arg_info->pass_by_reference) {
			return 0;
		}
	}

	/* Check return type compatibility, but only if the prototype already specifies
	 * a return type. Adding a new return type is always valid. */
	if (proto->common.fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
		/* Removing a return type is not valid. */
		if (!(fe->common.fn_flags & ZEND_ACC_HAS_RETURN_TYPE)) {
			return 0;
		}

		if (!zend_do_perform_type_hint_check(fe, fe->common.arg_info - 1, proto, proto->common.arg_info - 1)) {
			switch (ZEND_TYPE_CODE(proto->common.arg_info[-1].type)) {
				case IS_ITERABLE:
					if (!zend_iterable_compatibility_check(fe->common.arg_info - 1)) {
						return 0;
					}
					break;

				default:
					return 0;
			}
		}

		if (ZEND_TYPE_ALLOW_NULL(fe->common.arg_info[-1].type) && !ZEND_TYPE_ALLOW_NULL(proto->common.arg_info[-1].type)) {
			return 0;
		}
	}
	return 1;
}