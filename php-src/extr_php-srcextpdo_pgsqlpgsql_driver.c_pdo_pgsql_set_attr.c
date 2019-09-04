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
typedef  void* zend_bool ;
struct TYPE_4__ {void* disable_prepares; void* emulate_prepares; } ;
typedef  TYPE_1__ pdo_pgsql_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
#define  PDO_ATTR_EMULATE_PREPARES 129 
#define  PDO_PGSQL_ATTR_DISABLE_PREPARES 128 
 scalar_t__ zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_pgsql_set_attr(pdo_dbh_t *dbh, zend_long attr, zval *val)
{
	zend_bool bval = zval_get_long(val)? 1 : 0;
	pdo_pgsql_db_handle *H = (pdo_pgsql_db_handle *)dbh->driver_data;

	switch (attr) {
		case PDO_ATTR_EMULATE_PREPARES:
			H->emulate_prepares = bval;
			return 1;
		case PDO_PGSQL_ATTR_DISABLE_PREPARES:
			H->disable_prepares = bval;
			return 1;
		default:
			return 0;
	}
}