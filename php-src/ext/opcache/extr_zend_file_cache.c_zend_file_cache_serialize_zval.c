#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_14__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ zend_reference ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_file_cache_metainfo ;
typedef  TYPE_1__ zend_ast_ref ;
typedef  TYPE_1__ HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  GC_AST (TYPE_1__*) ; 
#define  IS_ARRAY 131 
#define  IS_CONSTANT_AST 130 
#define  IS_REFERENCE 129 
 int /*<<< orphan*/  IS_SERIALIZED (TYPE_1__*) ; 
#define  IS_STRING 128 
 int /*<<< orphan*/  SERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  SERIALIZE_STR (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 TYPE_1__* Z_ARR_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_AST_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_REF_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_serialize_ast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_file_cache_serialize_hash (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*)) ; 

__attribute__((used)) static void zend_file_cache_serialize_zval(zval                     *zv,
                                           zend_persistent_script   *script,
                                           zend_file_cache_metainfo *info,
                                           void                     *buf)
{
	switch (Z_TYPE_P(zv)) {
		case IS_STRING:
			if (!IS_SERIALIZED(Z_STR_P(zv))) {
				SERIALIZE_STR(Z_STR_P(zv));
			}
			break;
		case IS_ARRAY:
			if (!IS_SERIALIZED(Z_ARR_P(zv))) {
				HashTable *ht;

				SERIALIZE_PTR(Z_ARR_P(zv));
				ht = Z_ARR_P(zv);
				UNSERIALIZE_PTR(ht);
				zend_file_cache_serialize_hash(ht, script, info, buf, zend_file_cache_serialize_zval);
			}
			break;
		case IS_REFERENCE:
			if (!IS_SERIALIZED(Z_REF_P(zv))) {
				zend_reference *ref;

				SERIALIZE_PTR(Z_REF_P(zv));
				ref = Z_REF_P(zv);
				UNSERIALIZE_PTR(ref);
				zend_file_cache_serialize_zval(&ref->val, script, info, buf);
			}
			break;
		case IS_CONSTANT_AST:
			if (!IS_SERIALIZED(Z_AST_P(zv))) {
				zend_ast_ref *ast;

				SERIALIZE_PTR(Z_AST_P(zv));
				ast = Z_AST_P(zv);
				UNSERIALIZE_PTR(ast);
				zend_file_cache_serialize_ast(GC_AST(ast), script, info, buf);
			}
			break;
	}
}