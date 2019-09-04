#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * alias; int /*<<< orphan*/  modifiers; int /*<<< orphan*/  trait_method; } ;
typedef  TYPE_1__ zend_trait_alias ;
struct TYPE_10__ {int /*<<< orphan*/  attr; struct TYPE_10__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  trait_aliases; } ;

/* Variables and functions */
 TYPE_8__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_class_entry ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  zend_add_to_list (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ast_get_str (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_check_const_and_trait_alias_attr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_compile_method_ref (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_compile_trait_alias(zend_ast *ast) /* {{{ */
{
	zend_ast *method_ref_ast = ast->child[0];
	zend_ast *alias_ast = ast->child[1];
	uint32_t modifiers = ast->attr;

	zend_trait_alias *alias;

	zend_check_const_and_trait_alias_attr(modifiers, "method");

	alias = emalloc(sizeof(zend_trait_alias));
	zend_compile_method_ref(method_ref_ast, &alias->trait_method);
	alias->modifiers = modifiers;

	if (alias_ast) {
		alias->alias = zend_string_copy(zend_ast_get_str(alias_ast));
	} else {
		alias->alias = NULL;
	}

	zend_add_to_list(&CG(active_class_entry)->trait_aliases, alias);
}