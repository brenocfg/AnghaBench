#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_30__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_25__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
typedef  int /*<<< orphan*/  enum_mysqlnd_collected_stats ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_40__ {scalar_t__ (* read_result_metadata ) (TYPE_9__*,TYPE_12__*) ;int /*<<< orphan*/  (* free_result_contents ) (TYPE_9__*) ;} ;
struct TYPE_43__ {TYPE_6__ m; } ;
struct TYPE_42__ {TYPE_7__* data; } ;
struct TYPE_41__ {int /*<<< orphan*/  state; TYPE_9__* result; int /*<<< orphan*/  stmt_id; } ;
struct TYPE_39__ {TYPE_9__* (* result_init ) (int) ;} ;
struct TYPE_38__ {int /*<<< orphan*/  l; int /*<<< orphan*/  s; } ;
struct TYPE_37__ {int /*<<< orphan*/  l; int /*<<< orphan*/  s; } ;
struct TYPE_36__ {int /*<<< orphan*/  error; scalar_t__ error_no; } ;
struct TYPE_33__ {int /*<<< orphan*/  (* init_eof_packet ) (TYPE_10__*) ;int /*<<< orphan*/  (* init_rset_header_packet ) (TYPE_10__*) ;} ;
struct TYPE_35__ {TYPE_1__ m; } ;
struct TYPE_34__ {scalar_t__ error_no; } ;
struct TYPE_32__ {int field_count; int /*<<< orphan*/  stats; int /*<<< orphan*/  upsert_status; TYPE_9__* current_result; TYPE_2__* payload_decoder_factory; TYPE_25__* error_info; TYPE_5__* m; int /*<<< orphan*/  state; int /*<<< orphan*/  last_query_type; TYPE_4__ last_message; } ;
struct TYPE_31__ {int field_count; int server_status; int /*<<< orphan*/  warning_count; TYPE_3__ info_or_local_file; int /*<<< orphan*/  last_insert_id; int /*<<< orphan*/  affected_rows; TYPE_30__ error_info; } ;
typedef  TYPE_7__ MYSQLND_STMT_DATA ;
typedef  TYPE_8__ MYSQLND_STMT ;
typedef  TYPE_9__ MYSQLND_RES ;
typedef  TYPE_10__ MYSQLND_PACKET_RSET_HEADER ;
typedef  TYPE_10__ MYSQLND_PACKET_EOF ;
typedef  TYPE_12__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_FETCHING_DATA ; 
 int /*<<< orphan*/  CONN_NEXT_RESULT_PENDING ; 
 int /*<<< orphan*/  CONN_QUIT_SENT ; 
 int /*<<< orphan*/  CONN_READY ; 
 int /*<<< orphan*/  CONN_SENDING_LOAD_DATA ; 
 int /*<<< orphan*/  COPY_CLIENT_ERROR (TYPE_25__*,TYPE_30__) ; 
 scalar_t__ CR_SERVER_GONE_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_ERR_FMT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_INF (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  MYSQLND_INC_CONN_STATISTIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MYSQLND_NULL_LENGTH 128 
 int /*<<< orphan*/  MYSQLND_STMT_INITTED ; 
 int /*<<< orphan*/  PACKET_FREE (TYPE_10__*) ; 
 scalar_t__ PACKET_READ (TYPE_12__*,TYPE_10__*) ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  QUERY_LOAD_LOCAL ; 
 int /*<<< orphan*/  QUERY_SELECT ; 
 int /*<<< orphan*/  QUERY_UPSERT ; 
 int SERVER_MORE_RESULTS_EXISTS ; 
 int SERVER_QUERY_NO_GOOD_INDEX_USED ; 
 int SERVER_QUERY_NO_INDEX_USED ; 
 int SERVER_QUERY_WAS_SLOW ; 
 int /*<<< orphan*/  SET_CONNECTION_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EMPTY_MESSAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NEW_MESSAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_OOM_ERROR (TYPE_25__*) ; 
 int /*<<< orphan*/  STAT_BAD_INDEX_USED ; 
 int /*<<< orphan*/  STAT_LAST ; 
 int /*<<< orphan*/  STAT_NON_RSET_QUERY ; 
 int /*<<< orphan*/  STAT_NO_INDEX_USED ; 
 int /*<<< orphan*/  STAT_QUERY_WAS_SLOW ; 
 int /*<<< orphan*/  STAT_RSET_QUERY ; 
 int /*<<< orphan*/  TRUE ; 
 int UPSERT_STATUS_GET_SERVER_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_AFFECTED_ROWS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_AFFECTED_ROWS_TO_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_LAST_INSERT_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_SERVER_STATUS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_WARNINGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnd_efree (TYPE_9__*) ; 
 scalar_t__ mysqlnd_handle_local_infile (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*) ; 
 TYPE_9__* stub2 (int) ; 
 TYPE_9__* stub3 (int) ; 
 scalar_t__ stub4 (TYPE_9__*,TYPE_12__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_9__*) ; 

enum_func_status
mysqlnd_query_read_result_set_header(MYSQLND_CONN_DATA * conn, MYSQLND_STMT * s)
{
	enum_func_status ret;
	MYSQLND_STMT_DATA * stmt = s ? s->data : NULL;
	MYSQLND_PACKET_RSET_HEADER rset_header;
	MYSQLND_PACKET_EOF fields_eof;

	DBG_ENTER("mysqlnd_query_read_result_set_header");
	DBG_INF_FMT("stmt=%lu", stmt? stmt->stmt_id:0);

	ret = FAIL;
	do {
		conn->payload_decoder_factory->m.init_rset_header_packet(&rset_header);
		UPSERT_STATUS_SET_AFFECTED_ROWS_TO_ERROR(conn->upsert_status);

		if (FAIL == (ret = PACKET_READ(conn, &rset_header))) {
			if (conn->error_info->error_no != CR_SERVER_GONE_ERROR) {
				php_error_docref(NULL, E_WARNING, "Error reading result set's header");
			}
			break;
		}

		if (rset_header.error_info.error_no) {
			/*
			  Cover a protocol design error: error packet does not
			  contain the server status. Therefore, the client has no way
			  to find out whether there are more result sets of
			  a multiple-result-set statement pending. Luckily, in 5.0 an
			  error always aborts execution of a statement, wherever it is
			  a multi-statement or a stored procedure, so it should be
			  safe to unconditionally turn off the flag here.
			*/
			UPSERT_STATUS_SET_SERVER_STATUS(conn->upsert_status, UPSERT_STATUS_GET_SERVER_STATUS(conn->upsert_status) & ~SERVER_MORE_RESULTS_EXISTS);
			/*
			  This will copy the error code and the messages, as they
			  are buffers in the struct
			*/
			COPY_CLIENT_ERROR(conn->error_info, rset_header.error_info);
			ret = FAIL;
			DBG_ERR_FMT("error=%s", rset_header.error_info.error);
			/* Return back from CONN_QUERY_SENT */
			SET_CONNECTION_STATE(&conn->state, CONN_READY);
			break;
		}
		conn->error_info->error_no = 0;

		switch (rset_header.field_count) {
			case MYSQLND_NULL_LENGTH: {	/* LOAD DATA LOCAL INFILE */
				zend_bool is_warning;
				DBG_INF("LOAD DATA");
				conn->last_query_type = QUERY_LOAD_LOCAL;
				conn->field_count = 0; /* overwrite previous value, or the last value could be used and lead to bug#53503 */
				SET_CONNECTION_STATE(&conn->state, CONN_SENDING_LOAD_DATA);
				ret = mysqlnd_handle_local_infile(conn, rset_header.info_or_local_file.s, &is_warning);
				SET_CONNECTION_STATE(&conn->state,  (ret == PASS || is_warning == TRUE)? CONN_READY:CONN_QUIT_SENT);
				MYSQLND_INC_CONN_STATISTIC(conn->stats, STAT_NON_RSET_QUERY);
				break;
			}
			case 0:				/* UPSERT */
				DBG_INF("UPSERT");
				conn->last_query_type = QUERY_UPSERT;
				conn->field_count = rset_header.field_count;
				UPSERT_STATUS_RESET(conn->upsert_status);
				UPSERT_STATUS_SET_WARNINGS(conn->upsert_status, rset_header.warning_count);
				UPSERT_STATUS_SET_SERVER_STATUS(conn->upsert_status, rset_header.server_status);
				UPSERT_STATUS_SET_AFFECTED_ROWS(conn->upsert_status, rset_header.affected_rows);
				UPSERT_STATUS_SET_LAST_INSERT_ID(conn->upsert_status, rset_header.last_insert_id);
				SET_NEW_MESSAGE(conn->last_message.s, conn->last_message.l,
								rset_header.info_or_local_file.s, rset_header.info_or_local_file.l);
				/* Result set can follow UPSERT statement, check server_status */
				if (UPSERT_STATUS_GET_SERVER_STATUS(conn->upsert_status) & SERVER_MORE_RESULTS_EXISTS) {
					SET_CONNECTION_STATE(&conn->state, CONN_NEXT_RESULT_PENDING);
				} else {
					SET_CONNECTION_STATE(&conn->state, CONN_READY);
				}
				ret = PASS;
				MYSQLND_INC_CONN_STATISTIC(conn->stats, STAT_NON_RSET_QUERY);
				break;
			default: do {			/* Result set */
				MYSQLND_RES * result;
				enum_mysqlnd_collected_stats statistic = STAT_LAST;

				DBG_INF("Result set pending");
				SET_EMPTY_MESSAGE(conn->last_message.s, conn->last_message.l);

				MYSQLND_INC_CONN_STATISTIC(conn->stats, STAT_RSET_QUERY);
				UPSERT_STATUS_RESET(conn->upsert_status);
				/* restore after zeroing */
				UPSERT_STATUS_SET_AFFECTED_ROWS_TO_ERROR(conn->upsert_status);

				conn->last_query_type = QUERY_SELECT;
				SET_CONNECTION_STATE(&conn->state, CONN_FETCHING_DATA);
				/* PS has already allocated it */
				conn->field_count = rset_header.field_count;
				if (!stmt) {
					result = conn->current_result = conn->m->result_init(rset_header.field_count);
				} else {
					if (!stmt->result) {
						DBG_INF("This is 'SHOW'/'EXPLAIN'-like query.");
						/*
						  This is 'SHOW'/'EXPLAIN'-like query. Current implementation of
						  prepared statements can't send result set metadata for these queries
						  on prepare stage. Read it now.
						*/
						result = stmt->result = conn->m->result_init(rset_header.field_count);
					} else {
						/*
						  Update result set metadata if it for some reason changed between
						  prepare and execute, i.e.:
						  - in case of 'SELECT ?' we don't know column type unless data was
							supplied to mysql_stmt_execute, so updated column type is sent
							now.
						  - if data dictionary changed between prepare and execute, for
							example a table used in the query was altered.
						  Note, that now (4.1.3) we always send metadata in reply to
						  COM_STMT_EXECUTE (even if it is not necessary), so either this or
						  previous branch always works.
						*/
					}
					result = stmt->result;
				}
				if (!result) {
					SET_OOM_ERROR(conn->error_info);
					ret = FAIL;
					break;
				}

				if (FAIL == (ret = result->m.read_result_metadata(result, conn))) {
					/* For PS, we leave them in Prepared state */
					if (!stmt && conn->current_result) {
						mnd_efree(conn->current_result);
						conn->current_result = NULL;
					}
					DBG_ERR("Error occurred while reading metadata");
					break;
				}

				/* Check for SERVER_STATUS_MORE_RESULTS if needed */
				conn->payload_decoder_factory->m.init_eof_packet(&fields_eof);
				if (FAIL == (ret = PACKET_READ(conn, &fields_eof))) {
					DBG_ERR("Error occurred while reading the EOF packet");
					result->m.free_result_contents(result);
					if (!stmt) {
						conn->current_result = NULL;
					} else {
						stmt->result = NULL;
						/* XXX: This will crash, because we will null also the methods.
							But seems it happens in extreme cases or doesn't. Should be fixed by exporting a function
							(from mysqlnd_driver.c?) to do the reset.
							This is done also in mysqlnd_ps.c
						*/
						memset(stmt, 0, sizeof(*stmt));
						stmt->state = MYSQLND_STMT_INITTED;
					}
				} else {
					DBG_INF_FMT("warnings=%u server_status=%u", fields_eof.warning_count, fields_eof.server_status);
					UPSERT_STATUS_SET_WARNINGS(conn->upsert_status, fields_eof.warning_count);
					/*
					  If SERVER_MORE_RESULTS_EXISTS is set then this is either MULTI_QUERY or a CALL()
					  The first packet after sending the query/com_execute has the bit set only
					  in this cases. Not sure why it's a needed but it marks that the whole stream
					  will include many result sets. What actually matters are the bits set at the end
					  of every result set (the EOF packet).
					*/
					UPSERT_STATUS_SET_SERVER_STATUS(conn->upsert_status, fields_eof.server_status);
					if (fields_eof.server_status & SERVER_QUERY_NO_GOOD_INDEX_USED) {
						statistic = STAT_BAD_INDEX_USED;
					} else if (fields_eof.server_status & SERVER_QUERY_NO_INDEX_USED) {
						statistic = STAT_NO_INDEX_USED;
					} else if (fields_eof.server_status & SERVER_QUERY_WAS_SLOW) {
						statistic = STAT_QUERY_WAS_SLOW;
					}
					MYSQLND_INC_CONN_STATISTIC(conn->stats, statistic);
				}
			} while (0);
			PACKET_FREE(&fields_eof);
			break; /* switch break */
		}
	} while (0);
	PACKET_FREE(&rset_header);

	DBG_INF(ret == PASS? "PASS":"FAIL");
	DBG_RETURN(ret);
}