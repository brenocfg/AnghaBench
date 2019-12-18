#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int num_excludes; int /*<<< orphan*/ * exclude_class_names; int /*<<< orphan*/  trait_method; } ;
typedef  TYPE_1__ zend_trait_precedence ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_14__ {int children; TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_list ;
struct TYPE_15__ {struct TYPE_15__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  size_t uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  trait_precedences; } ;

/* Variables and functions */
 TYPE_11__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_class_entry ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  zend_add_to_list (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* zend_ast_get_list (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_compile_method_ref (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_resolve_class_name_ast (TYPE_3__*) ; 

__attribute__((used)) static void zend_compile_trait_precedence(zend_ast *ast) /* {{{ */
{
	zend_ast *method_ref_ast = ast->child[0];
	zend_ast *insteadof_ast = ast->child[1];
	zend_ast_list *insteadof_list = zend_ast_get_list(insteadof_ast);
	uint32_t i;

	zend_trait_precedence *precedence = emalloc(sizeof(zend_trait_precedence) + (insteadof_list->children - 1) * sizeof(zend_string*));
	zend_compile_method_ref(method_ref_ast, &precedence->trait_method);
	precedence->num_excludes = insteadof_list->children;

	for (i = 0; i < insteadof_list->children; ++i) {
		zend_ast *name_ast = insteadof_list->child[i];
		precedence->exclude_class_names[i] = zend_resolve_class_name_ast(name_ast);
	}

	zend_add_to_list(&CG(active_class_entry)->trait_precedences, precedence);
}