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
typedef  int /*<<< orphan*/  enum_func_status ;
struct TYPE_16__ {int /*<<< orphan*/  (* free_result_contents ) (TYPE_8__*) ;} ;
struct TYPE_21__ {TYPE_3__ m; } ;
struct TYPE_20__ {TYPE_2__* payload_decoder_factory; } ;
struct TYPE_19__ {int /*<<< orphan*/  warning_count; int /*<<< orphan*/  server_status; } ;
struct TYPE_18__ {TYPE_4__* data; } ;
struct TYPE_17__ {int /*<<< orphan*/  state; int /*<<< orphan*/  upsert_status; TYPE_8__* result; int /*<<< orphan*/  stmt_id; TYPE_7__* conn; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* init_eof_packet ) (TYPE_6__*) ;} ;
struct TYPE_15__ {TYPE_1__ m; } ;
typedef  TYPE_4__ MYSQLND_STMT_DATA ;
typedef  TYPE_5__ MYSQLND_STMT ;
typedef  TYPE_6__ MYSQLND_PACKET_EOF ;
typedef  TYPE_7__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MYSQLND_STMT_INITTED ; 
 int /*<<< orphan*/  MYSQLND_STMT_PREPARED ; 
 int /*<<< orphan*/  PACKET_READ (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_SERVER_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_WARNINGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_prepare_read_eof(MYSQLND_STMT * s)
{
	MYSQLND_STMT_DATA * stmt = s? s->data : NULL;
	MYSQLND_CONN_DATA * conn = stmt? stmt->conn : NULL;
	MYSQLND_PACKET_EOF fields_eof;
	enum_func_status ret = FAIL;

	DBG_ENTER("mysqlnd_stmt_prepare_read_eof");
	if (!stmt || !conn) {
		DBG_RETURN(FAIL);
	}
	DBG_INF_FMT("stmt=%lu", stmt->stmt_id);

	conn->payload_decoder_factory->m.init_eof_packet(&fields_eof);
	if (FAIL == (ret = PACKET_READ(conn, &fields_eof))) {
		if (stmt->result) {
			stmt->result->m.free_result_contents(stmt->result);
			/* XXX: This will crash, because we will null also the methods.
				But seems it happens in extreme cases or doesn't. Should be fixed by exporting a function
				(from mysqlnd_driver.c?) to do the reset.
				This bad handling is also in mysqlnd_result.c
			*/
			memset(stmt, 0, sizeof(MYSQLND_STMT_DATA));
			stmt->state = MYSQLND_STMT_INITTED;
		}
	} else {
		UPSERT_STATUS_SET_SERVER_STATUS(stmt->upsert_status, fields_eof.server_status);
		UPSERT_STATUS_SET_WARNINGS(stmt->upsert_status, fields_eof.warning_count);
		stmt->state = MYSQLND_STMT_PREPARED;
	}

	DBG_RETURN(ret);
}