#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_long ;
typedef  int /*<<< orphan*/  result ;
struct TYPE_10__ {int /*<<< orphan*/  isc_status; int /*<<< orphan*/  tr; } ;
typedef  TYPE_1__ pdo_firebird_db_handle ;
struct TYPE_11__ {scalar_t__ auto_commit; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  isc_stmt_handle ;
typedef  int /*<<< orphan*/  info_count ;
struct TYPE_12__ {int sqln; scalar_t__ sqld; int /*<<< orphan*/  version; } ;
typedef  TYPE_3__ XSQLDA ;

/* Variables and functions */
 int /*<<< orphan*/  DSQL_drop ; 
 int /*<<< orphan*/  PDO_FB_SQLDA_VERSION ; 
 int /*<<< orphan*/  PDO_FIREBIRD_HANDLE_INITIALIZER ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_2__*) ; 
 int /*<<< orphan*/  const_cast (char const*) ; 
 int /*<<< orphan*/  firebird_alloc_prepare_stmt (TYPE_2__*,char const*,size_t,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isc_commit_retaining (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_dsql_execute2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ isc_dsql_free_statement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isc_dsql_sql_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*) ; 
 char isc_info_end ; 
 char isc_info_req_select_count ; 
#define  isc_info_sql_records 128 
 unsigned int isc_vax_integer (char*,short) ; 

__attribute__((used)) static zend_long firebird_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len) /* {{{ */
{
	pdo_firebird_db_handle *H = (pdo_firebird_db_handle *)dbh->driver_data;
	isc_stmt_handle stmt = PDO_FIREBIRD_HANDLE_INITIALIZER;
	static char const info_count[] = { isc_info_sql_records };
	char result[64];
	int ret = 0;
	XSQLDA in_sqlda, out_sqlda;

	/* TODO no placeholders in exec() for now */
	in_sqlda.version = out_sqlda.version = PDO_FB_SQLDA_VERSION;
	in_sqlda.sqld = out_sqlda.sqld = 0;
	out_sqlda.sqln = 1;

	/* allocate and prepare statement */
	if (!firebird_alloc_prepare_stmt(dbh, sql, sql_len, &out_sqlda, &stmt, 0)) {
		return -1;
	}

	/* execute the statement */
	if (isc_dsql_execute2(H->isc_status, &H->tr, &stmt, PDO_FB_SQLDA_VERSION, &in_sqlda, &out_sqlda)) {
		RECORD_ERROR(dbh);
		ret = -1;
		goto free_statement;
	}

	/* find out how many rows were affected */
	if (isc_dsql_sql_info(H->isc_status, &stmt, sizeof(info_count), const_cast(info_count),
			sizeof(result),	result)) {
		RECORD_ERROR(dbh);
		ret = -1;
		goto free_statement;
	}

	if (result[0] == isc_info_sql_records) {
		unsigned i = 3, result_size = isc_vax_integer(&result[1],2);

		while (result[i] != isc_info_end && i < result_size) {
			short len = (short)isc_vax_integer(&result[i+1],2);
			if (result[i] != isc_info_req_select_count) {
				ret += isc_vax_integer(&result[i+3],len);
			}
			i += len+3;
		}
	}

	/* commit if we're in auto_commit mode */
	if (dbh->auto_commit && isc_commit_retaining(H->isc_status, &H->tr)) {
		RECORD_ERROR(dbh);
	}

free_statement:

	if (isc_dsql_free_statement(H->isc_status, &stmt, DSQL_drop)) {
		RECORD_ERROR(dbh);
	}

	return ret;
}