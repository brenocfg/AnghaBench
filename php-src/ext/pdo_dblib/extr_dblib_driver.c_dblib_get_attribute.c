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
struct TYPE_4__ {int /*<<< orphan*/  datetime_convert; int /*<<< orphan*/  skip_empty_rowsets; int /*<<< orphan*/  link; int /*<<< orphan*/  stringify_uniqueidentifier; int /*<<< orphan*/  assume_national_character_set_strings; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
#define  PDO_ATTR_DEFAULT_STR_PARAM 134 
#define  PDO_ATTR_EMULATE_PREPARES 133 
#define  PDO_DBLIB_ATTR_DATETIME_CONVERT 132 
#define  PDO_DBLIB_ATTR_SKIP_EMPTY_ROWSETS 131 
#define  PDO_DBLIB_ATTR_STRINGIFY_UNIQUEIDENTIFIER 130 
#define  PDO_DBLIB_ATTR_TDS_VERSION 129 
#define  PDO_DBLIB_ATTR_VERSION 128 
 int /*<<< orphan*/  PDO_PARAM_STR_CHAR ; 
 int /*<<< orphan*/  PDO_PARAM_STR_NATL ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dblib_get_tds_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbtds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbversion () ; 

__attribute__((used)) static int dblib_get_attribute(pdo_dbh_t *dbh, zend_long attr, zval *return_value)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;

	switch (attr) {
		case PDO_ATTR_DEFAULT_STR_PARAM:
			ZVAL_LONG(return_value, H->assume_national_character_set_strings ? PDO_PARAM_STR_NATL : PDO_PARAM_STR_CHAR);
			break;

		case PDO_ATTR_EMULATE_PREPARES:
			/* this is the only option available, but expose it so common tests and whatever else can introspect */
			ZVAL_TRUE(return_value);
			break;

		case PDO_DBLIB_ATTR_STRINGIFY_UNIQUEIDENTIFIER:
			ZVAL_BOOL(return_value, H->stringify_uniqueidentifier);
			break;

		case PDO_DBLIB_ATTR_VERSION:
			ZVAL_STRING(return_value, dbversion());
			break;

		case PDO_DBLIB_ATTR_TDS_VERSION:
			dblib_get_tds_version(return_value, dbtds(H->link));
			break;

		case PDO_DBLIB_ATTR_SKIP_EMPTY_ROWSETS:
			ZVAL_BOOL(return_value, H->skip_empty_rowsets);
			break;

		case PDO_DBLIB_ATTR_DATETIME_CONVERT:
			ZVAL_BOOL(return_value, H->datetime_convert);
			break;

		default:
			return 0;
	}

	return 1;
}