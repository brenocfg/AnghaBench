#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG (TYPE_2__*) ; 
 int FAILURE ; 
 int SUCCESS ; 
 scalar_t__ ZEND_AST_DECLARE ; 
 TYPE_1__* zend_ast_get_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_declare_is_first_statement(zend_ast *ast) /* {{{ */
{
	uint32_t i = 0;
	zend_ast_list *file_ast = zend_ast_get_list(CG(ast));

	/* Check to see if this declare is preceded only by declare statements */
	while (i < file_ast->children) {
		if (file_ast->child[i] == ast) {
			return SUCCESS;
		} else if (file_ast->child[i] == NULL) {
			/* Empty statements are not allowed prior to a declare */
			return FAILURE;
		} else if (file_ast->child[i]->kind != ZEND_AST_DECLARE) {
			/* declares can only be preceded by other declares */
			return FAILURE;
		}
		i++;
	}
	return FAILURE;
}