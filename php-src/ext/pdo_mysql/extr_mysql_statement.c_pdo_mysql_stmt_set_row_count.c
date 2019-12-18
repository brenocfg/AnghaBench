#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_long ;
struct TYPE_4__ {scalar_t__ row_count; TYPE_2__* driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;

/* Variables and functions */
 scalar_t__ mysql_stmt_affected_rows (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdo_mysql_stmt_set_row_count(pdo_stmt_t *stmt) /* {{{ */
{
	zend_long row_count;
	pdo_mysql_stmt *S = stmt->driver_data;
	row_count = (zend_long) mysql_stmt_affected_rows(S->stmt);
	if (row_count != (zend_long)-1) {
		stmt->row_count = row_count;
	}
}