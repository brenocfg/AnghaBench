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
struct TYPE_4__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ pdo_mysql_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (char*) ; 
 int /*<<< orphan*/  mysql_insert_id (int /*<<< orphan*/ ) ; 
 char* php_pdo_int64_to_str (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *pdo_mysql_last_insert_id(pdo_dbh_t *dbh, const char *name, size_t *len)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;
	char *id = php_pdo_int64_to_str(mysql_insert_id(H->server));
	PDO_DBG_ENTER("pdo_mysql_last_insert_id");
	*len = strlen(id);
	PDO_DBG_RETURN(id);
}