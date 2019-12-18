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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ pdo_sqlite_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
#define  PDO_ATTR_TIMEOUT 129 
#define  PDO_SQLITE_ATTR_EXTENDED_RESULT_CODES 128 
 int /*<<< orphan*/  sqlite3_busy_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_extended_result_codes (int /*<<< orphan*/ ,int) ; 
 int zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_sqlite_set_attr(pdo_dbh_t *dbh, zend_long attr, zval *val)
{
	pdo_sqlite_db_handle *H = (pdo_sqlite_db_handle *)dbh->driver_data;

	switch (attr) {
		case PDO_ATTR_TIMEOUT:
			sqlite3_busy_timeout(H->db, zval_get_long(val) * 1000);
			return 1;
		case PDO_SQLITE_ATTR_EXTENDED_RESULT_CODES:
			sqlite3_extended_result_codes(H->db, zval_get_long(val));
			return 1;
	}
	return 0;
}