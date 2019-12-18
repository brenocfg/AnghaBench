#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_5__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ pdo_stmt_t ;
typedef  int /*<<< orphan*/  pdo_error_type ;
struct TYPE_6__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void _firebird_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, char const *file, zend_long line) /* {{{ */
{
	pdo_error_type *const error_code = stmt ? &stmt->error_code : &dbh->error_code;

	strcpy(*error_code, "HY000");
}