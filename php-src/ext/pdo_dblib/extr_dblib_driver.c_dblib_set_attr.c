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
struct TYPE_4__ {int assume_national_character_set_strings; void* datetime_convert; int /*<<< orphan*/  skip_empty_rowsets; void* stringify_uniqueidentifier; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
#define  PDO_ATTR_DEFAULT_STR_PARAM 133 
#define  PDO_ATTR_TIMEOUT 132 
#define  PDO_DBLIB_ATTR_DATETIME_CONVERT 131 
#define  PDO_DBLIB_ATTR_QUERY_TIMEOUT 130 
#define  PDO_DBLIB_ATTR_SKIP_EMPTY_ROWSETS 129 
#define  PDO_DBLIB_ATTR_STRINGIFY_UNIQUEIDENTIFIER 128 
 void* PDO_PARAM_STR_NATL ; 
 int /*<<< orphan*/  SUCCEED ; 
 int /*<<< orphan*/  dbsettime (void*) ; 
 void* zval_get_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dblib_set_attr(pdo_dbh_t *dbh, zend_long attr, zval *val)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;

	switch(attr) {
		case PDO_ATTR_DEFAULT_STR_PARAM:
			H->assume_national_character_set_strings = zval_get_long(val) == PDO_PARAM_STR_NATL ? 1 : 0;
			return 1;
		case PDO_ATTR_TIMEOUT:
		case PDO_DBLIB_ATTR_QUERY_TIMEOUT:
			return SUCCEED == dbsettime(zval_get_long(val)) ? 1 : 0;
		case PDO_DBLIB_ATTR_STRINGIFY_UNIQUEIDENTIFIER:
			H->stringify_uniqueidentifier = zval_get_long(val);
			return 1;
		case PDO_DBLIB_ATTR_SKIP_EMPTY_ROWSETS:
			H->skip_empty_rowsets = zval_is_true(val);
			return 1;
		case PDO_DBLIB_ATTR_DATETIME_CONVERT:
			H->datetime_convert = zval_get_long(val);
			return 1;
		default:
			return 0;
	}
}