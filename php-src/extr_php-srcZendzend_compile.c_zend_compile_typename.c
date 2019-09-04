#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_uchar ;
typedef  int /*<<< orphan*/  zend_type ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_bool ;
struct TYPE_6__ {int attr; scalar_t__ kind; } ;
typedef  TYPE_1__ zend_ast ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ ZEND_AST_TYPE ; 
 scalar_t__ ZEND_FETCH_CLASS_DEFAULT ; 
 int ZEND_NAME_NOT_FQ ; 
 int /*<<< orphan*/  ZEND_TYPE_ENCODE (int,int) ; 
 int /*<<< orphan*/  ZEND_TYPE_ENCODE_CLASS (int /*<<< orphan*/ *,int) ; 
 int ZEND_TYPE_NULLABLE ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_assert_valid_class_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_ast_get_str (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ensure_valid_class_fetch_type (scalar_t__) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_get_class_fetch_type_ast (TYPE_1__*) ; 
 int zend_lookup_builtin_type_by_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_resolve_class_name_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_type zend_compile_typename(zend_ast *ast, zend_bool force_allow_null) /* {{{ */
{
	zend_bool allow_null = force_allow_null;
	if (ast->attr & ZEND_TYPE_NULLABLE) {
		allow_null = 1;
		ast->attr &= ~ZEND_TYPE_NULLABLE;
	}

	if (ast->kind == ZEND_AST_TYPE) {
		return ZEND_TYPE_ENCODE(ast->attr, allow_null);
	} else {
		zend_string *class_name = zend_ast_get_str(ast);
		zend_uchar type = zend_lookup_builtin_type_by_name(class_name);

		if (type != 0) {
			if ((ast->attr & ZEND_NAME_NOT_FQ) != ZEND_NAME_NOT_FQ) {
				zend_error_noreturn(E_COMPILE_ERROR,
					"Type declaration '%s' must be unqualified",
					ZSTR_VAL(zend_string_tolower(class_name)));
			}
			return ZEND_TYPE_ENCODE(type, allow_null);
		} else {
			uint32_t fetch_type = zend_get_class_fetch_type_ast(ast);
			if (fetch_type == ZEND_FETCH_CLASS_DEFAULT) {
				class_name = zend_resolve_class_name_ast(ast);
				zend_assert_valid_class_name(class_name);
			} else {
				zend_ensure_valid_class_fetch_type(fetch_type);
				zend_string_addref(class_name);
			}

			return ZEND_TYPE_ENCODE_CLASS(class_name, allow_null);
		}
	}
}