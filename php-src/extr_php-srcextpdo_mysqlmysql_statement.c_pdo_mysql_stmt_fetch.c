#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_9__ {int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_10__ {TYPE_6__* result; int /*<<< orphan*/  current_lengths; TYPE_1__* H; int /*<<< orphan*/ * current_data; scalar_t__ stmt; } ;
typedef  TYPE_3__ pdo_mysql_stmt ;
typedef  enum pdo_fetch_orientation { ____Placeholder_pdo_fetch_orientation } pdo_fetch_orientation ;
struct TYPE_11__ {int /*<<< orphan*/  eof; } ;
struct TYPE_8__ {int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int MYSQL_NO_DATA ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 scalar_t__ mysql_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_fetch_lengths (TYPE_6__*) ; 
 int /*<<< orphan*/ * mysql_fetch_row (TYPE_6__*) ; 
 int mysql_stmt_fetch (scalar_t__) ; 
 int /*<<< orphan*/  pdo_mysql_error_stmt (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pdo_mysql_stmt_fetch(pdo_stmt_t *stmt, enum pdo_fetch_orientation ori, zend_long offset) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;
#if PDO_USE_MYSQLND
	zend_bool fetched_anything;

	PDO_DBG_ENTER("pdo_mysql_stmt_fetch");
	PDO_DBG_INF_FMT("stmt=%p", S->stmt);
	if (S->stmt) {
		if (FAIL == mysqlnd_stmt_fetch(S->stmt, &fetched_anything) || fetched_anything == FALSE) {
			PDO_DBG_RETURN(0);
		}

		PDO_DBG_RETURN(1);
	}
#else
	int ret;

	if (S->stmt) {
		ret = mysql_stmt_fetch(S->stmt);

#		ifdef MYSQL_DATA_TRUNCATED
		if (ret == MYSQL_DATA_TRUNCATED) {
			ret = 0;
		}
#		endif

		if (ret) {
			if (ret != MYSQL_NO_DATA) {
				pdo_mysql_error_stmt(stmt);
			}
			PDO_DBG_RETURN(0);
		}

		PDO_DBG_RETURN(1);
	}
#endif /* PDO_USE_MYSQLND */

	if (!S->result) {
		strcpy(stmt->error_code, "HY000");
		PDO_DBG_RETURN(0);
	}
#if PDO_USE_MYSQLND
	if (!S->stmt && S->current_data) {
		mnd_free(S->current_data);
	}
#endif /* PDO_USE_MYSQLND */

	if ((S->current_data = mysql_fetch_row(S->result)) == NULL) {
#if PDO_USE_MYSQLND
		if (S->result->unbuf && !S->result->unbuf->eof_reached && mysql_errno(S->H->server)) {
#else
		if (!S->result->eof && mysql_errno(S->H->server)) {
#endif
			pdo_mysql_error_stmt(stmt);
		}
		PDO_DBG_RETURN(0);
	}

	S->current_lengths = mysql_fetch_lengths(S->result);
	PDO_DBG_RETURN(1);
}