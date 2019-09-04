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
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_6__ {int /*<<< orphan*/ * stmt; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_sqlite_stmt_dtor(pdo_stmt_t *stmt)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;

	if (S->stmt) {
		sqlite3_finalize(S->stmt);
		S->stmt = NULL;
	}
	efree(S);
	return 1;
}