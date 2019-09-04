#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ enum_func_status ;
struct TYPE_17__ {int /*<<< orphan*/  field_count; int /*<<< orphan*/  upsert_status; int /*<<< orphan*/  error_info; TYPE_2__* payload_decoder_factory; } ;
struct TYPE_16__ {int error_code; int /*<<< orphan*/  param_count; int /*<<< orphan*/  field_count; int /*<<< orphan*/  warning_count; int /*<<< orphan*/  stmt_id; int /*<<< orphan*/  error_info; } ;
struct TYPE_15__ {TYPE_3__* data; } ;
struct TYPE_14__ {int /*<<< orphan*/  param_count; int /*<<< orphan*/  field_count; int /*<<< orphan*/  upsert_status; int /*<<< orphan*/  stmt_id; int /*<<< orphan*/  error_info; TYPE_6__* conn; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* init_prepare_response_packet ) (TYPE_5__*) ;} ;
struct TYPE_13__ {TYPE_1__ m; } ;
typedef  TYPE_3__ MYSQLND_STMT_DATA ;
typedef  TYPE_4__ MYSQLND_STMT ;
typedef  TYPE_5__ MYSQLND_PACKET_PREPARE_RESPONSE ;
typedef  TYPE_6__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_CLIENT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  PACKET_FREE (TYPE_5__*) ; 
 scalar_t__ PACKET_READ (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_AFFECTED_ROWS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPSERT_STATUS_SET_WARNINGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_read_prepare_response(MYSQLND_STMT * s)
{
	MYSQLND_STMT_DATA * stmt = s? s->data : NULL;
	MYSQLND_CONN_DATA * conn = stmt? stmt->conn : NULL;
	MYSQLND_PACKET_PREPARE_RESPONSE prepare_resp;
	enum_func_status ret = FAIL;

	DBG_ENTER("mysqlnd_stmt_read_prepare_response");
	if (!stmt || !conn) {
		DBG_RETURN(FAIL);
	}
	DBG_INF_FMT("stmt=%lu", stmt->stmt_id);

	conn->payload_decoder_factory->m.init_prepare_response_packet(&prepare_resp);

	if (FAIL == PACKET_READ(conn, &prepare_resp)) {
		goto done;
	}

	if (0xFF == prepare_resp.error_code) {
		COPY_CLIENT_ERROR(stmt->error_info, prepare_resp.error_info);
		COPY_CLIENT_ERROR(conn->error_info, prepare_resp.error_info);
		goto done;
	}
	ret = PASS;
	stmt->stmt_id = prepare_resp.stmt_id;
	UPSERT_STATUS_SET_WARNINGS(conn->upsert_status, prepare_resp.warning_count);
	UPSERT_STATUS_SET_AFFECTED_ROWS(stmt->upsert_status, 0);  /* be like libmysql */
	stmt->field_count = conn->field_count = prepare_resp.field_count;
	stmt->param_count = prepare_resp.param_count;
done:
	PACKET_FREE(&prepare_resp);

	DBG_RETURN(ret);
}