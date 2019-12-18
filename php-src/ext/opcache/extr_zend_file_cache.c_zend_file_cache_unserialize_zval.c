#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ zend_reference ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
#define  IS_ARRAY 131 
#define  IS_CONSTANT_AST 130 
#define  IS_REFERENCE 129 
#define  IS_STRING 128 
 int /*<<< orphan*/  IS_UNSERIALIZED (void*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (void*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (void*) ; 
 int /*<<< orphan*/  ZVAL_PTR_DTOR ; 
 void* Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ASTVAL_P (int /*<<< orphan*/ *) ; 
 void* Z_AST_P (int /*<<< orphan*/ *) ; 
 void* Z_REF_P (int /*<<< orphan*/ *) ; 
 void* Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_ast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_file_cache_unserialize_zval(zval                    *zv,
                                             zend_persistent_script  *script,
                                             void                    *buf)
{
	switch (Z_TYPE_P(zv)) {
		case IS_STRING:
			if (!IS_UNSERIALIZED(Z_STR_P(zv))) {
				UNSERIALIZE_STR(Z_STR_P(zv));
			}
			break;
		case IS_ARRAY:
			if (!IS_UNSERIALIZED(Z_ARR_P(zv))) {
				HashTable *ht;

				UNSERIALIZE_PTR(Z_ARR_P(zv));
				ht = Z_ARR_P(zv);
				zend_file_cache_unserialize_hash(ht,
						script, buf, zend_file_cache_unserialize_zval, ZVAL_PTR_DTOR);
			}
			break;
		case IS_REFERENCE:
			if (!IS_UNSERIALIZED(Z_REF_P(zv))) {
				zend_reference *ref;

				UNSERIALIZE_PTR(Z_REF_P(zv));
				ref = Z_REF_P(zv);
				zend_file_cache_unserialize_zval(&ref->val, script, buf);
			}
			break;
		case IS_CONSTANT_AST:
			if (!IS_UNSERIALIZED(Z_AST_P(zv))) {
				UNSERIALIZE_PTR(Z_AST_P(zv));
				zend_file_cache_unserialize_ast(Z_ASTVAL_P(zv), script, buf);
			}
			break;
	}
}