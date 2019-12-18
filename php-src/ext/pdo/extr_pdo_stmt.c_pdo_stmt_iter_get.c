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
typedef  scalar_t__ zend_ulong ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/ * funcs; } ;
typedef  TYPE_1__ zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct php_pdo_iterator {TYPE_1__ iter; int /*<<< orphan*/  fetch_ahead; scalar_t__ key; } ;
typedef  int /*<<< orphan*/  pdo_stmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_FETCH_ORI_NEXT ; 
 int /*<<< orphan*/  PDO_FETCH_USE_DEFAULT ; 
 int /*<<< orphan*/  PDO_HANDLE_STMT_ERR () ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_PDO_STMT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fetch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct php_pdo_iterator* ecalloc (int,int) ; 
 int /*<<< orphan*/  pdo_stmt_iter_funcs ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

zend_object_iterator *pdo_stmt_iter_get(zend_class_entry *ce, zval *object, int by_ref)
{
	pdo_stmt_t *stmt = Z_PDO_STMT_P(object);
	struct php_pdo_iterator *I;

	if (by_ref) {
		zend_throw_error(NULL, "An iterator cannot be used with foreach by reference");
		return NULL;
	}

	I = ecalloc(1, sizeof(struct php_pdo_iterator));
	zend_iterator_init(&I->iter);
	I->iter.funcs = &pdo_stmt_iter_funcs;
	Z_ADDREF_P(object);
	ZVAL_OBJ(&I->iter.data, Z_OBJ_P(object));

	if (!do_fetch(stmt, 1, &I->fetch_ahead, PDO_FETCH_USE_DEFAULT,
			PDO_FETCH_ORI_NEXT, 0, 0)) {
		PDO_HANDLE_STMT_ERR();
		I->key = (zend_ulong)-1;
		ZVAL_UNDEF(&I->fetch_ahead);
	}

	return &I->iter;
}