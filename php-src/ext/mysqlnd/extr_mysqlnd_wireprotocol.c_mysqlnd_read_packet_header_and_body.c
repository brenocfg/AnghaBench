#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  enum_func_status ;
typedef  enum mysqlnd_packet_type { ____Placeholder_mysqlnd_packet_type } mysqlnd_packet_type ;
struct TYPE_13__ {size_t const size; } ;
struct TYPE_12__ {TYPE_2__* data; } ;
struct TYPE_10__ {scalar_t__ (* receive ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {TYPE_1__ m; } ;
typedef  int /*<<< orphan*/  MYSQLND_VIO ;
typedef  int /*<<< orphan*/  MYSQLND_STATS ;
typedef  TYPE_3__ MYSQLND_PFC ;
typedef  TYPE_4__ MYSQLND_PACKET_HEADER ;
typedef  int /*<<< orphan*/  MYSQLND_ERROR_INFO ;
typedef  int /*<<< orphan*/  MYSQLND_CONNECTION_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_QUIT_SENT ; 
 int /*<<< orphan*/  CR_SERVER_GONE_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_ERR_FMT (char*,...) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ * const,size_t const) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ MYSQLND_HEADER_SIZE ; 
 int /*<<< orphan*/  MYSQLND_INC_CONN_STATISTIC_W_VALUE2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_CLIENT_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_CONNECTION_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNKNOWN_SQLSTATE ; 
 scalar_t__ mysqlnd_read_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysqlnd_server_gone ; 
 int /*<<< orphan*/ * packet_type_to_statistic_byte_count ; 
 int /*<<< orphan*/ * packet_type_to_statistic_packet_count ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum_func_status
mysqlnd_read_packet_header_and_body(MYSQLND_PACKET_HEADER * packet_header,
									MYSQLND_PFC * pfc,
									MYSQLND_VIO * vio,
									MYSQLND_STATS * stats,
									MYSQLND_ERROR_INFO * error_info,
									MYSQLND_CONNECTION_STATE * connection_state,
									zend_uchar * const buf, const size_t buf_size,
									const char * const packet_type_as_text,
									enum mysqlnd_packet_type packet_type)
{
	DBG_ENTER("mysqlnd_read_packet_header_and_body");
	DBG_INF_FMT("buf=%p size=%u", buf, buf_size);
	if (FAIL == mysqlnd_read_header(pfc, vio, packet_header, stats, error_info)) {
		SET_CONNECTION_STATE(connection_state, CONN_QUIT_SENT);
		SET_CLIENT_ERROR(error_info, CR_SERVER_GONE_ERROR, UNKNOWN_SQLSTATE, mysqlnd_server_gone);
		DBG_ERR_FMT("Can't read %s's header", packet_type_as_text);
		DBG_RETURN(FAIL);
	}
	if (buf_size < packet_header->size) {
		DBG_ERR_FMT("Packet buffer %u wasn't big enough %u, %u bytes will be unread",
					buf_size, packet_header->size, packet_header->size - buf_size);
		DBG_RETURN(FAIL);
	}
	if (FAIL == pfc->data->m.receive(pfc, vio, buf, packet_header->size, stats, error_info)) {
		SET_CONNECTION_STATE(connection_state, CONN_QUIT_SENT);
		SET_CLIENT_ERROR(error_info, CR_SERVER_GONE_ERROR, UNKNOWN_SQLSTATE, mysqlnd_server_gone);
		DBG_ERR_FMT("Empty '%s' packet body", packet_type_as_text);
		DBG_RETURN(FAIL);
	}
	MYSQLND_INC_CONN_STATISTIC_W_VALUE2(stats, packet_type_to_statistic_byte_count[packet_type],
										MYSQLND_HEADER_SIZE + packet_header->size,
										packet_type_to_statistic_packet_count[packet_type],
										1);
	DBG_RETURN(PASS);
}