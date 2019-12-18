#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
struct TYPE_8__ {int children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_9__ {struct TYPE_9__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZEND_JMPZ ; 
 int /*<<< orphan*/  efree (size_t*) ; 
 size_t* safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_ast_get_list (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_compile_expr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_compile_stmt (TYPE_2__*) ; 
 size_t zend_emit_cond_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t zend_emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_update_jump_target_to_next (size_t) ; 

void zend_compile_if(zend_ast *ast) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;
	uint32_t *jmp_opnums = NULL;

	if (list->children > 1) {
		jmp_opnums = safe_emalloc(sizeof(uint32_t), list->children - 1, 0);
	}

	for (i = 0; i < list->children; ++i) {
		zend_ast *elem_ast = list->child[i];
		zend_ast *cond_ast = elem_ast->child[0];
		zend_ast *stmt_ast = elem_ast->child[1];

		if (cond_ast) {
			znode cond_node;
			uint32_t opnum_jmpz;
			zend_compile_expr(&cond_node, cond_ast);
			opnum_jmpz = zend_emit_cond_jump(ZEND_JMPZ, &cond_node, 0);

			zend_compile_stmt(stmt_ast);

			if (i != list->children - 1) {
				jmp_opnums[i] = zend_emit_jump(0);
			}
			zend_update_jump_target_to_next(opnum_jmpz);
		} else {
			/* "else" can only occur as last element. */
			ZEND_ASSERT(i == list->children - 1);
			zend_compile_stmt(stmt_ast);
		}
	}

	if (list->children > 1) {
		for (i = 0; i < list->children - 1; ++i) {
			zend_update_jump_target_to_next(jmp_opnums[i]);
		}
		efree(jmp_opnums);
	}
}