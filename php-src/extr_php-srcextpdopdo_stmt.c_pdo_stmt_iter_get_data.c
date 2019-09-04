#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct php_pdo_iterator {int /*<<< orphan*/  fetch_ahead; } ;

/* Variables and functions */
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *pdo_stmt_iter_get_data(zend_object_iterator *iter)
{
	struct php_pdo_iterator *I = (struct php_pdo_iterator*)iter;

	/* sanity */
	if (Z_ISUNDEF(I->fetch_ahead)) {
		return NULL;
	}

	return &I->fetch_ahead;
}