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
struct TYPE_4__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_cursor_closer(pdo_stmt_t *stmt)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	sqlite3_reset(S->stmt);
	return 1;
}