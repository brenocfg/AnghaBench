#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ zend_constant ;

/* Variables and functions */
 int CG (int /*<<< orphan*/ ) ; 
 int CONST_NO_FILE_CACHE ; 
 int CONST_PERSISTENT ; 
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int ZEND_COMPILE_WITH_FILE_CACHE ; 
 int ZEND_CONSTANT_FLAGS (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compiler_options ; 
 int /*<<< orphan*/  zend_constants ; 
 int /*<<< orphan*/ * zend_get_special_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int zend_optimizer_get_persistent_constant(zend_string *name, zval *result, int copy)
{
	zval *zv;
	zend_constant *c = zend_hash_find_ptr(EG(zend_constants), name);
	if (c) {
		if ((ZEND_CONSTANT_FLAGS(c) & CONST_PERSISTENT)
		 && (!(ZEND_CONSTANT_FLAGS(c) & CONST_NO_FILE_CACHE)
		  || !(CG(compiler_options) & ZEND_COMPILE_WITH_FILE_CACHE))) {
			ZVAL_COPY_VALUE(result, &c->value);
			if (copy) {
				Z_TRY_ADDREF_P(result);
			}
			return 1;
		} else {
			return 0;
		}
	}

	/* Special constants null/true/false can always be substituted. */
	zv = zend_get_special_const(ZSTR_VAL(name), ZSTR_LEN(name));
	if (zv) {
		ZVAL_COPY_VALUE(result, zv);
		return 1;
	}
	return 0;
}