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
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_6__ {int done; int /*<<< orphan*/  stmt; scalar_t__ pre_fetched; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;
typedef  enum pdo_fetch_orientation { ____Placeholder_pdo_fetch_orientation } pdo_fetch_orientation ;

/* Variables and functions */
#define  SQLITE_DONE 130 
#define  SQLITE_ERROR 129 
#define  SQLITE_ROW 128 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_stmt_fetch(pdo_stmt_t *stmt,
	enum pdo_fetch_orientation ori, zend_long offset)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	int i;
	if (!S->stmt) {
		return 0;
	}
	if (S->pre_fetched) {
		S->pre_fetched = 0;
		return 1;
	}
	if (S->done) {
		return 0;
	}
	i = sqlite3_step(S->stmt);
	switch (i) {
		case SQLITE_ROW:
			return 1;

		case SQLITE_DONE:
			S->done = 1;
			sqlite3_reset(S->stmt);
			return 0;

		case SQLITE_ERROR:
			sqlite3_reset(S->stmt);
		default:
			pdo_sqlite_error_stmt(stmt);
			return 0;
	}
}