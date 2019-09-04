#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attr; struct TYPE_5__** child; } ;
typedef  TYPE_1__ zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  zend_compile_prop_decl (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void zend_compile_prop_group(zend_ast *list) /* {{{ */
{
	zend_ast *type_ast = list->child[0];
	zend_ast *prop_ast = list->child[1];

	zend_compile_prop_decl(prop_ast, type_ast, list->attr);
}