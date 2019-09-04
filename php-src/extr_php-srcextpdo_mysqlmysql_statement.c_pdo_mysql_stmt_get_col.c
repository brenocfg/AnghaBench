#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int column_count; int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_7__ {char** current_data; size_t* out_length; size_t* current_lengths; TYPE_1__* bound_result; scalar_t__* out_null; scalar_t__ stmt; int /*<<< orphan*/  result; } ;
typedef  TYPE_3__ pdo_mysql_stmt ;
struct TYPE_5__ {char* buffer; size_t buffer_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,scalar_t__) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pdo_mysql_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, size_t *len, int *caller_frees) /* {{{ */
{
	pdo_mysql_stmt *S = (pdo_mysql_stmt*)stmt->driver_data;

	PDO_DBG_ENTER("pdo_mysql_stmt_get_col");
	PDO_DBG_INF_FMT("stmt=%p", S->stmt);
	if (!S->result) {
		PDO_DBG_RETURN(0);
	}

	/* With mysqlnd data is stored inside mysqlnd, not S->current_data */
	if (!S->stmt) {
		if (S->current_data == NULL || !S->result) {
			PDO_DBG_RETURN(0);
		}
	}

	if (colno >= stmt->column_count) {
		/* error invalid column */
		PDO_DBG_RETURN(0);
	}
#if PDO_USE_MYSQLND
	if (S->stmt) {
		Z_TRY_ADDREF(S->stmt->data->result_bind[colno].zv);
		*ptr = (char*)&S->stmt->data->result_bind[colno].zv;
		*len = sizeof(zval);
		PDO_DBG_RETURN(1);
	}
#else
	if (S->stmt) {
		if (S->out_null[colno]) {
			*ptr = NULL;
			*len = 0;
			PDO_DBG_RETURN(1);
		}
		*ptr = S->bound_result[colno].buffer;
		if (S->out_length[colno] > S->bound_result[colno].buffer_length) {
			/* mysql lied about the column width */
			strcpy(stmt->error_code, "01004"); /* truncated */
			S->out_length[colno] = S->bound_result[colno].buffer_length;
			*len = S->out_length[colno];
			PDO_DBG_RETURN(0);
		}
		*len = S->out_length[colno];
		PDO_DBG_RETURN(1);
	}
#endif
	*ptr = S->current_data[colno];
	*len = S->current_lengths[colno];
	PDO_DBG_RETURN(1);
}