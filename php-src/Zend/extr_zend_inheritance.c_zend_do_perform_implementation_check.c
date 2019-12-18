#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; int fn_flags; scalar_t__ required_num_args; size_t num_args; TYPE_3__* arg_info; TYPE_4__* scope; } ;
struct TYPE_14__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ zend_arg_info ;
typedef  size_t uint32_t ;
typedef  scalar_t__ inheritance_status ;
struct TYPE_16__ {int ce_flags; } ;

/* Variables and functions */
 scalar_t__ INHERITANCE_ERROR ; 
 scalar_t__ INHERITANCE_SUCCESS ; 
 scalar_t__ INHERITANCE_UNRESOLVED ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_CTOR ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_INTERFACE ; 
 int ZEND_ACC_PRIVATE ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int ZEND_ACC_VARIADIC ; 
 scalar_t__ ZEND_ARG_SEND_MODE (TYPE_3__*) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 scalar_t__ zend_do_perform_arg_type_hint_check (TYPE_2__ const*,TYPE_3__*,TYPE_2__ const*,TYPE_3__*) ; 
 scalar_t__ zend_perform_covariant_type_check (TYPE_4__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inheritance_status zend_do_perform_implementation_check(
		const zend_function *fe, const zend_function *proto) /* {{{ */
{
	uint32_t i, num_args;
	inheritance_status status, local_status;

	/* If it's a user function then arg_info == NULL means we don't have any parameters but
	 * we still need to do the arg number checks.  We are only willing to ignore this for internal
	 * functions because extensions don't always define arg_info.
	 */
	if (!proto->common.arg_info && proto->common.type != ZEND_USER_FUNCTION) {
		return INHERITANCE_SUCCESS;
	}

	/* Checks for constructors only if they are declared in an interface,
	 * or explicitly marked as abstract
	 */
	ZEND_ASSERT(!((fe->common.fn_flags & ZEND_ACC_CTOR)
		&& ((proto->common.scope->ce_flags & ZEND_ACC_INTERFACE) == 0
			&& (proto->common.fn_flags & ZEND_ACC_ABSTRACT) == 0)));

	/* If the prototype method is private do not enforce a signature */
	ZEND_ASSERT(!(proto->common.fn_flags & ZEND_ACC_PRIVATE));

	/* check number of arguments */
	if (proto->common.required_num_args < fe->common.required_num_args
		|| proto->common.num_args > fe->common.num_args) {
		return INHERITANCE_ERROR;
	}

	/* by-ref constraints on return values are covariant */
	if ((proto->common.fn_flags & ZEND_ACC_RETURN_REFERENCE)
		&& !(fe->common.fn_flags & ZEND_ACC_RETURN_REFERENCE)) {
		return INHERITANCE_ERROR;
	}

	if ((proto->common.fn_flags & ZEND_ACC_VARIADIC)
		&& !(fe->common.fn_flags & ZEND_ACC_VARIADIC)) {
		return INHERITANCE_ERROR;
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

	status = INHERITANCE_SUCCESS;
	for (i = 0; i < num_args; i++) {
		zend_arg_info *fe_arg_info = &fe->common.arg_info[i];

		zend_arg_info *proto_arg_info;
		if (i < proto->common.num_args) {
			proto_arg_info = &proto->common.arg_info[i];
		} else {
			proto_arg_info = &proto->common.arg_info[proto->common.num_args];
		}

		local_status = zend_do_perform_arg_type_hint_check(fe, fe_arg_info, proto, proto_arg_info);

		if (UNEXPECTED(local_status != INHERITANCE_SUCCESS)) {
			if (UNEXPECTED(local_status == INHERITANCE_ERROR)) {
				return INHERITANCE_ERROR;
			}
			ZEND_ASSERT(local_status == INHERITANCE_UNRESOLVED);
			status = INHERITANCE_UNRESOLVED;
		}

		/* by-ref constraints on arguments are invariant */
		if (ZEND_ARG_SEND_MODE(fe_arg_info) != ZEND_ARG_SEND_MODE(proto_arg_info)) {
			return INHERITANCE_ERROR;
		}
	}

	/* Check return type compatibility, but only if the prototype already specifies
	 * a return type. Adding a new return type is always valid. */
	if (proto->common.fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
		/* Removing a return type is not valid. */
		if (!(fe->common.fn_flags & ZEND_ACC_HAS_RETURN_TYPE)) {
			return INHERITANCE_ERROR;
		}

		local_status = zend_perform_covariant_type_check(
			fe->common.scope, fe->common.arg_info[-1].type,
			proto->common.scope, proto->common.arg_info[-1].type);

		if (UNEXPECTED(local_status != INHERITANCE_SUCCESS)) {
			if (UNEXPECTED(local_status == INHERITANCE_ERROR)) {
				return INHERITANCE_ERROR;
			}
			ZEND_ASSERT(local_status == INHERITANCE_UNRESOLVED);
			status = INHERITANCE_UNRESOLVED;
		}
	}

	return status;
}