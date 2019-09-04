#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__* scope; } ;
struct TYPE_15__ {TYPE_3__ common; } ;
typedef  TYPE_4__ zend_function ;
struct TYPE_16__ {scalar_t__ type; } ;
typedef  TYPE_5__ zend_class_entry ;
struct TYPE_17__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ zend_arg_info ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_1__* parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 scalar_t__ ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char const* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 TYPE_5__* zend_lookup_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zend_do_perform_type_hint_check(const zend_function *fe, zend_arg_info *fe_arg_info, const zend_function *proto, zend_arg_info *proto_arg_info) /* {{{ */
{
	ZEND_ASSERT(ZEND_TYPE_IS_SET(fe_arg_info->type) && ZEND_TYPE_IS_SET(proto_arg_info->type));

	if (ZEND_TYPE_IS_CLASS(fe_arg_info->type) && ZEND_TYPE_IS_CLASS(proto_arg_info->type)) {
		zend_string *fe_class_name, *proto_class_name;
		const char *class_name;
		size_t class_name_len;

		fe_class_name = ZEND_TYPE_NAME(fe_arg_info->type);
		class_name = ZSTR_VAL(fe_class_name);
		class_name_len = ZSTR_LEN(fe_class_name);
		if (class_name_len == sizeof("parent")-1 && !strcasecmp(class_name, "parent") && proto->common.scope) {
			fe_class_name = zend_string_copy(proto->common.scope->name);
		} else if (class_name_len == sizeof("self")-1 && !strcasecmp(class_name, "self") && fe->common.scope) {
			fe_class_name = zend_string_copy(fe->common.scope->name);
		} else {
			zend_string_addref(fe_class_name);
		}

		proto_class_name = ZEND_TYPE_NAME(proto_arg_info->type);
		class_name = ZSTR_VAL(proto_class_name);
		class_name_len = ZSTR_LEN(proto_class_name);
		if (class_name_len == sizeof("parent")-1 && !strcasecmp(class_name, "parent") && proto->common.scope && proto->common.scope->parent) {
			proto_class_name = zend_string_copy(proto->common.scope->parent->name);
		} else if (class_name_len == sizeof("self")-1 && !strcasecmp(class_name, "self") && proto->common.scope) {
			proto_class_name = zend_string_copy(proto->common.scope->name);
		} else {
			zend_string_addref(proto_class_name);
		}

		if (fe_class_name != proto_class_name && strcasecmp(ZSTR_VAL(fe_class_name), ZSTR_VAL(proto_class_name)) != 0) {
			if (fe->common.type != ZEND_USER_FUNCTION) {
				zend_string_release(proto_class_name);
				zend_string_release(fe_class_name);
				return 0;
			} else {
				zend_class_entry *fe_ce, *proto_ce;

				fe_ce = zend_lookup_class(fe_class_name);
				proto_ce = zend_lookup_class(proto_class_name);

				/* Check for class alias */
				if (!fe_ce || !proto_ce ||
						fe_ce->type == ZEND_INTERNAL_CLASS ||
						proto_ce->type == ZEND_INTERNAL_CLASS ||
						fe_ce != proto_ce) {
					zend_string_release(proto_class_name);
					zend_string_release(fe_class_name);
					return 0;
				}
			}
		}
		zend_string_release(proto_class_name);
		zend_string_release(fe_class_name);
	} else if (ZEND_TYPE_CODE(fe_arg_info->type) != ZEND_TYPE_CODE(proto_arg_info->type)) {
		/* Incompatible built-in types */
		return 0;
	}

	return 1;
}