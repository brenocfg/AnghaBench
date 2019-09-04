#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ ZEND_AST_CALL ; 
 scalar_t__ ZEND_AST_METHOD_CALL ; 
 scalar_t__ ZEND_AST_STATIC_CALL ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void zend_ensure_writable_variable(const zend_ast *ast) /* {{{ */
{
	if (ast->kind == ZEND_AST_CALL) {
		zend_error_noreturn(E_COMPILE_ERROR, "Can't use function return value in write context");
	}
	if (ast->kind == ZEND_AST_METHOD_CALL || ast->kind == ZEND_AST_STATIC_CALL) {
		zend_error_noreturn(E_COMPILE_ERROR, "Can't use method return value in write context");
	}
}