#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_type ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_14__ {int ce_flags; int /*<<< orphan*/ * name; int /*<<< orphan*/  properties_info; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_15__ {int children; TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_list ;
struct TYPE_16__ {struct TYPE_16__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  int uint32_t ;

/* Variables and functions */
 TYPE_1__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_CALLABLE ; 
 scalar_t__ IS_DOUBLE ; 
 scalar_t__ IS_ITERABLE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_VOID ; 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_FINAL ; 
 int ZEND_ACC_INTERFACE ; 
 int /*<<< orphan*/  ZEND_SAME_FAKE_TYPE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ZEND_TYPE_ALLOW_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 char const* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_class_entry ; 
 TYPE_2__* zend_ast_get_list (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ast_get_str (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ast_get_zval (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_compile_typename (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_const_expr_to_zval (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_declare_typed_property (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,...) ; 
 char const* zend_get_type_by_const (scalar_t__) ; 
 scalar_t__ zend_hash_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_make_interned_string (int /*<<< orphan*/ ) ; 

void zend_compile_prop_decl(zend_ast *ast, zend_ast *type_ast, uint32_t flags) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	zend_class_entry *ce = CG(active_class_entry);
	uint32_t i, children = list->children;

	if (ce->ce_flags & ZEND_ACC_INTERFACE) {
		zend_error_noreturn(E_COMPILE_ERROR, "Interfaces may not include member variables");
	}

	if (flags & ZEND_ACC_ABSTRACT) {
		zend_error_noreturn(E_COMPILE_ERROR, "Properties cannot be declared abstract");
	}

	for (i = 0; i < children; ++i) {
		zend_ast *prop_ast = list->child[i];
		zend_ast *name_ast = prop_ast->child[0];
		zend_ast *value_ast = prop_ast->child[1];
		zend_ast *doc_comment_ast = prop_ast->child[2];
		zend_string *name = zval_make_interned_string(zend_ast_get_zval(name_ast));
		zend_string *doc_comment = NULL;
		zval value_zv;
		zend_type type = 0;

		if (type_ast) {
			type = zend_compile_typename(type_ast, 0);

			if (ZEND_TYPE_CODE(type) == IS_VOID || ZEND_TYPE_CODE(type) == IS_CALLABLE) {
				zend_error_noreturn(E_COMPILE_ERROR,
					"Property %s::$%s cannot have type %s",
					ZSTR_VAL(ce->name),
					ZSTR_VAL(name),
					zend_get_type_by_const(ZEND_TYPE_CODE(type)));
			}
		}

		/* Doc comment has been appended as last element in ZEND_AST_PROP_ELEM ast */
		if (doc_comment_ast) {
			doc_comment = zend_string_copy(zend_ast_get_str(doc_comment_ast));
		}

		if (flags & ZEND_ACC_FINAL) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot declare property %s::$%s final, "
				"the final modifier is allowed only for methods and classes",
				ZSTR_VAL(ce->name), ZSTR_VAL(name));
		}

		if (zend_hash_exists(&ce->properties_info, name)) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot redeclare %s::$%s",
				ZSTR_VAL(ce->name), ZSTR_VAL(name));
		}

		if (value_ast) {
			zend_const_expr_to_zval(&value_zv, value_ast);

			if (ZEND_TYPE_IS_SET(type) && !Z_CONSTANT(value_zv)) {
				if (Z_TYPE(value_zv) == IS_NULL) {
					if (!ZEND_TYPE_ALLOW_NULL(type)) {
						const char *name = ZEND_TYPE_IS_CLASS(type)
							? ZSTR_VAL(ZEND_TYPE_NAME(type)) : zend_get_type_by_const(ZEND_TYPE_CODE(type));
						zend_error_noreturn(E_COMPILE_ERROR,
								"Default value for property of type %s may not be null. "
								"Use the nullable type ?%s to allow null default value",
								name, name);
					}
				} else if (ZEND_TYPE_IS_CLASS(type)) {
					zend_error_noreturn(E_COMPILE_ERROR,
							"Property of type %s may not have default value", ZSTR_VAL(ZEND_TYPE_NAME(type)));
				} else if (ZEND_TYPE_CODE(type) == IS_ARRAY || ZEND_TYPE_CODE(type) == IS_ITERABLE) {
					if (Z_TYPE(value_zv) != IS_ARRAY) {
						zend_error_noreturn(E_COMPILE_ERROR,
								"Default value for property of type %s can only be an array",
								zend_get_type_by_const(ZEND_TYPE_CODE(type)));
					}
				} else if (ZEND_TYPE_CODE(type) == IS_DOUBLE) {
					if (Z_TYPE(value_zv) != IS_DOUBLE && Z_TYPE(value_zv) != IS_LONG) {
						zend_error_noreturn(E_COMPILE_ERROR,
								"Default value for property of type float can only be float or int");
					}
				} else if (!ZEND_SAME_FAKE_TYPE(ZEND_TYPE_CODE(type), Z_TYPE(value_zv))) {
					zend_error_noreturn(E_COMPILE_ERROR,
							"Default value for property of type %s can only be %s",
							zend_get_type_by_const(ZEND_TYPE_CODE(type)),
							zend_get_type_by_const(ZEND_TYPE_CODE(type)));
				}
			}
		} else if (!ZEND_TYPE_IS_SET(type)) {
			ZVAL_NULL(&value_zv);
		} else {
			ZVAL_UNDEF(&value_zv);
		}

		zend_declare_typed_property(ce, name, &value_zv, flags, doc_comment, type);
	}
}