#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_6__ {int row_count; int /*<<< orphan*/  error_code; int /*<<< orphan*/  executed; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {int exhausted; scalar_t__ statement_type; int /*<<< orphan*/  out_sqlda; int /*<<< orphan*/  stmt; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_firebird_stmt ;
struct TYPE_8__ {char* last_app_error; scalar_t__* isc_status; } ;
typedef  TYPE_3__ pdo_firebird_db_handle ;
typedef  enum pdo_fetch_orientation { ____Placeholder_pdo_fetch_orientation } pdo_fetch_orientation ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_FB_SQLDA_VERSION ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_1__*) ; 
 scalar_t__ isc_dsql_fetch (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_info_sql_stmt_exec_procedure ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int firebird_stmt_fetch(pdo_stmt_t *stmt, /* {{{ */
	enum pdo_fetch_orientation ori, zend_long offset)
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;
	pdo_firebird_db_handle *H = S->H;

	if (!stmt->executed) {
		strcpy(stmt->error_code, "HY000");
		H->last_app_error = "Cannot fetch from a closed cursor";
	} else if (!S->exhausted) {
		if (S->statement_type == isc_info_sql_stmt_exec_procedure) {
			stmt->row_count = 1;
			S->exhausted = 1;
			return 1;
		}
		if (isc_dsql_fetch(H->isc_status, &S->stmt, PDO_FB_SQLDA_VERSION, &S->out_sqlda)) {
			if (H->isc_status[0] && H->isc_status[1]) {
				RECORD_ERROR(stmt);
			}
			S->exhausted = 1;
			return 0;
		}
		stmt->row_count++;
		return 1;
	}
	return 0;
}