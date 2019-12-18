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
typedef  int zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  link; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  scalar_t__ RETCODE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int DBCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  dbcanquery (int /*<<< orphan*/ ) ; 
 scalar_t__ dbcmd (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dbnextrow (int /*<<< orphan*/ ) ; 
 scalar_t__ dbnumcols (int /*<<< orphan*/ ) ; 
 scalar_t__ dbresults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbsetuserdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dbsqlexec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_long dblib_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;
	RETCODE ret, resret;

	dbsetuserdata(H->link, (BYTE*)&H->err);

	if (FAIL == dbcmd(H->link, sql)) {
		return -1;
	}

	if (FAIL == dbsqlexec(H->link)) {
		return -1;
	}

	resret = dbresults(H->link);

	if (resret == FAIL) {
		return -1;
	}

	ret = dbnextrow(H->link);
	if (ret == FAIL) {
		return -1;
	}

	if (dbnumcols(H->link) <= 0) {
		return DBCOUNT(H->link);
	}

	/* throw away any rows it might have returned */
	dbcanquery(H->link);

	return DBCOUNT(H->link);
}