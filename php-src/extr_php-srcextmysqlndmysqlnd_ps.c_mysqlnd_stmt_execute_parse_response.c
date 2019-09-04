#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enum_mysqlnd_parse_exec_response_type ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_21__ {scalar_t__ last_query_type; int /*<<< orphan*/  stats; int /*<<< orphan*/  state; scalar_t__ field_count; TYPE_1__* m; int /*<<< orphan*/  upsert_status; int /*<<< orphan*/ * error_info; } ;
struct TYPE_20__ {TYPE_5__* m; TYPE_6__* data; } ;
struct TYPE_19__ {int send_types_to_server; int flags; int /*<<< orphan*/  upsert_status; int /*<<< orphan*/  default_rset_handler; int /*<<< orphan*/  cursor_exists; int /*<<< orphan*/  state; scalar_t__ field_count; TYPE_4__* result; int /*<<< orphan*/ * error_info; TYPE_8__* conn; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* free_stmt_content ) (TYPE_7__* const) ;int /*<<< orphan*/  use_result; int /*<<< orphan*/  store_result; } ;
struct TYPE_17__ {TYPE_3__* unbuf; TYPE_2__* stored_data; scalar_t__ field_count; scalar_t__ conn; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lengths; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lengths; } ;
struct TYPE_14__ {scalar_t__ (* query_read_result_set_header ) (TYPE_8__*,TYPE_7__* const) ;scalar_t__ (* get_reference ) (TYPE_8__*) ;} ;
typedef  TYPE_6__ MYSQLND_STMT_DATA ;
typedef  TYPE_7__ MYSQLND_STMT ;
typedef  TYPE_8__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_QUERY_SENT ; 
 scalar_t__ CONN_QUIT_SENT ; 
 int /*<<< orphan*/  CONN_READY ; 
 int /*<<< orphan*/  COPY_CLIENT_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int CURSOR_TYPE_READ_ONLY ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int,int) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ GET_CONNECTION_STATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MYSQLND_INC_CONN_STATISTIC_W_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MYSQLND_PARSE_EXEC_RESPONSE_IMPLICIT_OUT_VARIABLES ; 
 int /*<<< orphan*/  MYSQLND_RES_PS_BUF ; 
 int /*<<< orphan*/  MYSQLND_STMT_EXECUTED ; 
 int /*<<< orphan*/  MYSQLND_STMT_PREPARED ; 
 int /*<<< orphan*/  MYSQLND_STMT_WAITING_USE_OR_STORE ; 
 scalar_t__ PASS ; 
 scalar_t__ QUERY_LOAD_LOCAL ; 
 scalar_t__ QUERY_UPSERT ; 
 int SERVER_PS_OUT_PARAMS ; 
 int SERVER_STATUS_CURSOR_EXISTS ; 
 int /*<<< orphan*/  SET_CONNECTION_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EMPTY_ERROR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAT_ROWS_AFFECTED_PS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UPSERT_STATUS_GET_AFFECTED_ROWS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_GET_LAST_INSERT_ID (int /*<<< orphan*/ ) ; 
 int UPSERT_STATUS_GET_SERVER_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_GET_WARNINGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_AFFECTED_ROWS (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_LAST_INSERT_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_SERVER_STATUS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_WARNINGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_8__*,TYPE_7__* const) ; 
 scalar_t__ stub2 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__* const) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_execute_parse_response(MYSQLND_STMT * const s, enum_mysqlnd_parse_exec_response_type type)
{
	MYSQLND_STMT_DATA * stmt = s? s->data : NULL;
	MYSQLND_CONN_DATA * conn = stmt? stmt->conn : NULL;
	enum_func_status ret;

	DBG_ENTER("mysqlnd_stmt_execute_parse_response");
	if (!stmt || !conn) {
		DBG_RETURN(FAIL);
	}
	SET_CONNECTION_STATE(&conn->state, CONN_QUERY_SENT);

	ret = conn->m->query_read_result_set_header(conn, s);
	if (ret == FAIL) {
		COPY_CLIENT_ERROR(stmt->error_info, *conn->error_info);
		UPSERT_STATUS_RESET(stmt->upsert_status);
		UPSERT_STATUS_SET_AFFECTED_ROWS(stmt->upsert_status, UPSERT_STATUS_GET_AFFECTED_ROWS(conn->upsert_status));
		if (GET_CONNECTION_STATE(&conn->state) == CONN_QUIT_SENT) {
			/* close the statement here, the connection has been closed */
		}
		stmt->state = MYSQLND_STMT_PREPARED;
		stmt->send_types_to_server = 1;
	} else {
		/*
		  stmt->send_types_to_server has already been set to 0 in
		  mysqlnd_stmt_execute_generate_request / mysqlnd_stmt_execute_store_params
		  In case there is a situation in which binding was done for integer and the
		  value is > LONG_MAX or < LONG_MIN, there is string conversion and we have
		  to resend the types. Next execution will also need to resend the type.
		*/
		SET_EMPTY_ERROR(stmt->error_info);
		SET_EMPTY_ERROR(conn->error_info);
		UPSERT_STATUS_SET_WARNINGS(stmt->upsert_status, UPSERT_STATUS_GET_WARNINGS(conn->upsert_status));
		UPSERT_STATUS_SET_AFFECTED_ROWS(stmt->upsert_status, UPSERT_STATUS_GET_AFFECTED_ROWS(conn->upsert_status));
		UPSERT_STATUS_SET_SERVER_STATUS(stmt->upsert_status, UPSERT_STATUS_GET_SERVER_STATUS(conn->upsert_status));
		UPSERT_STATUS_SET_LAST_INSERT_ID(stmt->upsert_status, UPSERT_STATUS_GET_LAST_INSERT_ID(conn->upsert_status));

		stmt->state = MYSQLND_STMT_EXECUTED;
		if (conn->last_query_type == QUERY_UPSERT || conn->last_query_type == QUERY_LOAD_LOCAL) {
			DBG_INF("PASS");
			DBG_RETURN(PASS);
		}

		stmt->result->type = MYSQLND_RES_PS_BUF;
		if (!stmt->result->conn) {
			/*
			  For SHOW we don't create (bypasses PS in server)
			  a result set at prepare and thus a connection was missing
			*/
			stmt->result->conn = conn->m->get_reference(conn);
		}

		/* Update stmt->field_count as SHOW sets it to 0 at prepare */
		stmt->field_count = stmt->result->field_count = conn->field_count;
		if (stmt->result->stored_data) {
			stmt->result->stored_data->lengths = NULL;
		} else if (stmt->result->unbuf) {
			stmt->result->unbuf->lengths = NULL;
		}
		if (stmt->field_count) {
			stmt->state = MYSQLND_STMT_WAITING_USE_OR_STORE;
			/*
			  We need to set this because the user might not call
			  use_result() or store_result() and we should be able to scrap the
			  data on the line, if he just decides to close the statement.
			*/
			DBG_INF_FMT("server_status=%u cursor=%u", UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status),
						UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status) & SERVER_STATUS_CURSOR_EXISTS);

			if (UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status) & SERVER_STATUS_CURSOR_EXISTS) {
				DBG_INF("cursor exists");
				stmt->cursor_exists = TRUE;
				SET_CONNECTION_STATE(&conn->state, CONN_READY);
				/* Only cursor read */
				stmt->default_rset_handler = s->m->use_result;
				DBG_INF("use_result");
			} else if (stmt->flags & CURSOR_TYPE_READ_ONLY) {
				DBG_INF("asked for cursor but got none");
				/*
				  We have asked for CURSOR but got no cursor, because the condition
				  above is not fulfilled. Then...

				  This is a single-row result set, a result set with no rows, EXPLAIN,
				  SHOW VARIABLES, or some other command which either a) bypasses the
				  cursors framework in the server and writes rows directly to the
				  network or b) is more efficient if all (few) result set rows are
				  precached on client and server's resources are freed.
				*/
				/* preferred is buffered read */
				stmt->default_rset_handler = s->m->store_result;
				DBG_INF("store_result");
			} else {
				DBG_INF("no cursor");
				/* preferred is unbuffered read */
				stmt->default_rset_handler = s->m->use_result;
				DBG_INF("use_result");
			}
		}
	}
#ifndef MYSQLND_DONT_SKIP_OUT_PARAMS_RESULTSET
	if (UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status) & SERVER_PS_OUT_PARAMS) {
		s->m->free_stmt_content(s);
		DBG_INF("PS OUT Variable RSet, skipping");
		/* OUT params result set. Skip for now to retain compatibility */
		ret = mysqlnd_stmt_execute_parse_response(s, MYSQLND_PARSE_EXEC_RESPONSE_IMPLICIT_OUT_VARIABLES);
	}
#endif

	DBG_INF_FMT("server_status=%u cursor=%u", UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status), UPSERT_STATUS_GET_SERVER_STATUS(stmt->upsert_status) & SERVER_STATUS_CURSOR_EXISTS);

	if (ret == PASS && conn->last_query_type == QUERY_UPSERT && UPSERT_STATUS_GET_AFFECTED_ROWS(stmt->upsert_status)) {
		MYSQLND_INC_CONN_STATISTIC_W_VALUE(conn->stats, STAT_ROWS_AFFECTED_PS, UPSERT_STATUS_GET_AFFECTED_ROWS(stmt->upsert_status));
	}

	DBG_INF(ret == PASS? "PASS":"FAIL");
	DBG_RETURN(ret);
}