#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_file_cache_metainfo ;
struct TYPE_12__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ zend_ast_zval ;
struct TYPE_13__ {size_t children; TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_list ;
struct TYPE_14__ {scalar_t__ kind; struct TYPE_14__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SERIALIZED (TYPE_3__*) ; 
 int /*<<< orphan*/  SERIALIZE_PTR (TYPE_3__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_3__*) ; 
 scalar_t__ ZEND_AST_CONSTANT ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 TYPE_2__* zend_ast_get_list (TYPE_3__*) ; 
 size_t zend_ast_get_num_children (TYPE_3__*) ; 
 scalar_t__ zend_ast_is_list (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_file_cache_serialize_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_serialize_ast(zend_ast                 *ast,
                                          zend_persistent_script   *script,
                                          zend_file_cache_metainfo *info,
                                          void                     *buf)
{
	uint32_t i;
	zend_ast *tmp;

	if (ast->kind == ZEND_AST_ZVAL || ast->kind == ZEND_AST_CONSTANT) {
		zend_file_cache_serialize_zval(&((zend_ast_zval*)ast)->val, script, info, buf);
	} else if (zend_ast_is_list(ast)) {
		zend_ast_list *list = zend_ast_get_list(ast);
		for (i = 0; i < list->children; i++) {
			if (list->child[i] && !IS_SERIALIZED(list->child[i])) {
				SERIALIZE_PTR(list->child[i]);
				tmp = list->child[i];
				UNSERIALIZE_PTR(tmp);
				zend_file_cache_serialize_ast(tmp, script, info, buf);
			}
		}
	} else {
		uint32_t children = zend_ast_get_num_children(ast);
		for (i = 0; i < children; i++) {
			if (ast->child[i] && !IS_SERIALIZED(ast->child[i])) {
				SERIALIZE_PTR(ast->child[i]);
				tmp = ast->child[i];
				UNSERIALIZE_PTR(tmp);
				zend_file_cache_serialize_ast(tmp, script, info, buf);
			}
		}
	}
}