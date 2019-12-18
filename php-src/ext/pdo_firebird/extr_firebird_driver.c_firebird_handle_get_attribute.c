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
struct TYPE_4__ {int fetch_table_names; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ pdo_firebird_db_handle ;
struct TYPE_5__ {int /*<<< orphan*/  auto_commit; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  (* info_func_t ) (char*) ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char*) ; 
#define  PDO_ATTR_AUTOCOMMIT 133 
#define  PDO_ATTR_CLIENT_VERSION 132 
#define  PDO_ATTR_CONNECTION_STATUS 131 
#define  PDO_ATTR_FETCH_TABLE_NAMES 130 
#define  PDO_ATTR_SERVER_INFO 129 
#define  PDO_ATTR_SERVER_VERSION 128 
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dlsym (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  firebird_info_cb ; 
 int /*<<< orphan*/  isc_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int firebird_handle_get_attribute(pdo_dbh_t *dbh, zend_long attr, zval *val) /* {{{ */
{
	pdo_firebird_db_handle *H = (pdo_firebird_db_handle *)dbh->driver_data;

	switch (attr) {
		char tmp[512];

		case PDO_ATTR_AUTOCOMMIT:
			ZVAL_LONG(val,dbh->auto_commit);
			return 1;

		case PDO_ATTR_CONNECTION_STATUS:
			ZVAL_BOOL(val, !isc_version(&H->db, firebird_info_cb, NULL));
			return 1;

		case PDO_ATTR_CLIENT_VERSION: {
#if defined(__GNUC__) || defined(PHP_WIN32)
			info_func_t info_func = NULL;
#ifdef __GNUC__
			info_func = (info_func_t)dlsym(RTLD_DEFAULT, "isc_get_client_version");
#else
			HMODULE l = GetModuleHandle("fbclient");

			if (!l) {
				break;
			}
			info_func = (info_func_t)GetProcAddress(l, "isc_get_client_version");
#endif
			if (info_func) {
				info_func(tmp);
				ZVAL_STRING(val, tmp);
			}
#else
			ZVAL_NULL(val);
#endif
			}
			return 1;

		case PDO_ATTR_SERVER_VERSION:
		case PDO_ATTR_SERVER_INFO:
			*tmp = 0;

			if (!isc_version(&H->db, firebird_info_cb, (void*)tmp)) {
				ZVAL_STRING(val, tmp);
				return 1;
			}

		case PDO_ATTR_FETCH_TABLE_NAMES:
			ZVAL_BOOL(val, H->fetch_table_names);
			return 1;
	}
	return 0;
}