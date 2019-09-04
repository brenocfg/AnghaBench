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
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  pdo_stmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  php_pdo_free_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_pdo_stmt_fetch_object (int /*<<< orphan*/ *) ; 

void pdo_dbstmt_free_storage(zend_object *std)
{
	pdo_stmt_t *stmt = php_pdo_stmt_fetch_object(std);
	php_pdo_free_statement(stmt);
}