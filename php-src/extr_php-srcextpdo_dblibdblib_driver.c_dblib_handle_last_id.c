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
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  scalar_t__ RETCODE ;
typedef  int /*<<< orphan*/  DBINT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 scalar_t__ NO_MORE_RESULTS ; 
 scalar_t__ NO_MORE_ROWS ; 
 int /*<<< orphan*/  SQLCHAR ; 
 int /*<<< orphan*/  dbcancel (int /*<<< orphan*/ ) ; 
 scalar_t__ dbcmd (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbcoltype (int /*<<< orphan*/ ,int) ; 
 size_t dbconvert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdata (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dbdatlen (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dbnextrow (int /*<<< orphan*/ ) ; 
 scalar_t__ dbresults (int /*<<< orphan*/ ) ; 
 scalar_t__ dbsqlexec (int /*<<< orphan*/ ) ; 
 char* emalloc (int) ; 

char *dblib_handle_last_id(pdo_dbh_t *dbh, const char *name, size_t *len)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;

	RETCODE ret;
	char *id = NULL;

	/*
	 * Would use scope_identity() but it's not implemented on Sybase
	 */

	if (FAIL == dbcmd(H->link, "SELECT @@IDENTITY")) {
		return NULL;
	}

	if (FAIL == dbsqlexec(H->link)) {
		return NULL;
	}

	ret = dbresults(H->link);
	if (ret == FAIL || ret == NO_MORE_RESULTS) {
		dbcancel(H->link);
		return NULL;
	}

	ret = dbnextrow(H->link);

	if (ret == FAIL || ret == NO_MORE_ROWS) {
		dbcancel(H->link);
		return NULL;
	}

	if (dbdatlen(H->link, 1) == 0) {
		dbcancel(H->link);
		return NULL;
	}

	id = emalloc(32);
	*len = dbconvert(NULL, (dbcoltype(H->link, 1)) , (dbdata(H->link, 1)) , (dbdatlen(H->link, 1)), SQLCHAR, (BYTE *)id, (DBINT)-1);

	dbcancel(H->link);
	return id;
}