#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * class_name; int /*<<< orphan*/  method_name; } ;
typedef  TYPE_1__ zend_trait_method_reference ;
struct TYPE_8__ {struct TYPE_8__** child; } ;
typedef  TYPE_2__ zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  zend_ast_get_str (TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_resolve_class_name_ast (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_compile_method_ref(zend_ast *ast, zend_trait_method_reference *method_ref) /* {{{ */
{
	zend_ast *class_ast = ast->child[0];
	zend_ast *method_ast = ast->child[1];

	method_ref->method_name = zend_string_copy(zend_ast_get_str(method_ast));

	if (class_ast) {
		method_ref->class_name = zend_resolve_class_name_ast(class_ast);
	} else {
		method_ref->class_name = NULL;
	}
}