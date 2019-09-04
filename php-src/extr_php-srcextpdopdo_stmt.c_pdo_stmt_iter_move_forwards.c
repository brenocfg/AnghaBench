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
typedef  scalar_t__ zend_ulong ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct php_pdo_iterator {scalar_t__ key; int /*<<< orphan*/  fetch_ahead; TYPE_1__ iter; } ;
typedef  int /*<<< orphan*/  pdo_stmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_FETCH_ORI_NEXT ; 
 int /*<<< orphan*/  PDO_FETCH_USE_DEFAULT ; 
 int /*<<< orphan*/  PDO_HANDLE_STMT_ERR () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_PDO_STMT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdo_stmt_iter_move_forwards(zend_object_iterator *iter)
{
	struct php_pdo_iterator *I = (struct php_pdo_iterator*)iter;
	pdo_stmt_t *stmt = Z_PDO_STMT_P(&I->iter.data); /* for PDO_HANDLE_STMT_ERR() */

	if (!Z_ISUNDEF(I->fetch_ahead)) {
		zval_ptr_dtor(&I->fetch_ahead);
	}

	if (!do_fetch(stmt, TRUE, &I->fetch_ahead, PDO_FETCH_USE_DEFAULT,
			PDO_FETCH_ORI_NEXT, 0, 0)) {

		PDO_HANDLE_STMT_ERR();
		I->key = (zend_ulong)-1;
		ZVAL_UNDEF(&I->fetch_ahead);

		return;
	}

	I->key++;
}