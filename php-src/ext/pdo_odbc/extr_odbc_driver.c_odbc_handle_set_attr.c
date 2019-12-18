#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_5__ {char* what; int /*<<< orphan*/  last_state; int /*<<< orphan*/  last_err_msg; } ;
struct TYPE_6__ {TYPE_1__ einfo; int /*<<< orphan*/  assume_utf8; } ;
typedef  TYPE_2__ pdo_odbc_db_handle ;
struct TYPE_7__ {scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_dbh_t ;

/* Variables and functions */
#define  PDO_ODBC_ATTR_ASSUME_UTF8 128 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zval_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int odbc_handle_set_attr(pdo_dbh_t *dbh, zend_long attr, zval *val)
{
	pdo_odbc_db_handle *H = (pdo_odbc_db_handle *)dbh->driver_data;
	switch (attr) {
		case PDO_ODBC_ATTR_ASSUME_UTF8:
			H->assume_utf8 = zval_is_true(val);
			return 1;
		default:
			strcpy(H->einfo.last_err_msg, "Unknown Attribute");
			H->einfo.what = "setAttribute";
			strcpy(H->einfo.last_state, "IM001");
			return 0;
	}
}