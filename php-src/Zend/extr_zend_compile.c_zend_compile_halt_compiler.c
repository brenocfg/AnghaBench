#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_4__ {struct TYPE_4__** child; } ;
typedef  TYPE_1__ zend_ast ;
typedef  int /*<<< orphan*/  const_name ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_CS ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ FC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_bracketed_namespaces ; 
 int /*<<< orphan*/  in_namespace ; 
 int /*<<< orphan*/  zend_ast_get_zval (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zend_get_compiled_filename () ; 
 int /*<<< orphan*/ * zend_mangle_property_name (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_register_long_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zend_compile_halt_compiler(zend_ast *ast) /* {{{ */
{
	zend_ast *offset_ast = ast->child[0];
	zend_long offset = Z_LVAL_P(zend_ast_get_zval(offset_ast));

	zend_string *filename, *name;
	const char const_name[] = "__COMPILER_HALT_OFFSET__";

	if (FC(has_bracketed_namespaces) && FC(in_namespace)) {
		zend_error_noreturn(E_COMPILE_ERROR,
			"__HALT_COMPILER() can only be used from the outermost scope");
	}

	filename = zend_get_compiled_filename();
	name = zend_mangle_property_name(const_name, sizeof(const_name) - 1,
		ZSTR_VAL(filename), ZSTR_LEN(filename), 0);

	zend_register_long_constant(ZSTR_VAL(name), ZSTR_LEN(name), offset, CONST_CS, 0);
	zend_string_release_ex(name, 0);
}