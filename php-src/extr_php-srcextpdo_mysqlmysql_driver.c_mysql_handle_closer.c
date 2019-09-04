#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* errmsg; } ;
struct TYPE_8__ {TYPE_1__ einfo; scalar_t__ server; } ;
typedef  TYPE_2__ pdo_mysql_db_handle ;
struct TYPE_9__ {int /*<<< orphan*/ * driver_data; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_3__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_close (scalar_t__) ; 
 int /*<<< orphan*/  pefree (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mysql_handle_closer(pdo_dbh_t *dbh)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;

	PDO_DBG_ENTER("mysql_handle_closer");
	PDO_DBG_INF_FMT("dbh=%p", dbh);
	if (H) {
		if (H->server) {
			mysql_close(H->server);
		}
		if (H->einfo.errmsg) {
			pefree(H->einfo.errmsg, dbh->is_persistent);
		}
		pefree(H, dbh->is_persistent);
		dbh->driver_data = NULL;
	}
	PDO_DBG_RETURN(0);
}