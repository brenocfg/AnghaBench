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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct php_pdo_iterator {int /*<<< orphan*/  fetch_ahead; } ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_stmt_iter_valid(zend_object_iterator *iter)
{
	struct php_pdo_iterator *I = (struct php_pdo_iterator*)iter;

	return Z_ISUNDEF(I->fetch_ahead) ? FAILURE : SUCCESS;
}