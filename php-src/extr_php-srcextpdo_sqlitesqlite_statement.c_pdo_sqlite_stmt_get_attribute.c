#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_3__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
typedef  int /*<<< orphan*/  pdo_sqlite_stmt ;

/* Variables and functions */
#define  PDO_SQLITE_ATTR_READONLY_STATEMENT 128 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_sqlite_stmt_get_attribute(pdo_stmt_t *stmt, zend_long attr, zval *val)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;

	switch (attr) {
		case PDO_SQLITE_ATTR_READONLY_STATEMENT:
			ZVAL_FALSE(val);

#if SQLITE_VERSION_NUMBER >= 3007004
				if (sqlite3_stmt_readonly(S->stmt)) {
					ZVAL_TRUE(val);
				}
#endif
			break;

		default:
			return 0;
	}

	return 1;
}