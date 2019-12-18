#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_function_entry ;
typedef  int /*<<< orphan*/  pdo_dbh_t ;

/* Variables and functions */
#define  PDO_DBH_DRIVER_METHOD_KIND_DBH 128 
 int /*<<< orphan*/  const* dbh_methods ; 

__attribute__((used)) static const zend_function_entry *pdo_pgsql_get_driver_methods(pdo_dbh_t *dbh, int kind)
{
	switch (kind) {
		case PDO_DBH_DRIVER_METHOD_KIND_DBH:
			return dbh_methods;
		default:
			return NULL;
	}
}