#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_25__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  scalar_t__ zend_bool ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_42__ {size_t auth_data_len; scalar_t__ is_change_user_packet; char* user; char* db; size_t db_len; scalar_t__ silent; char* auth_plugin_name; int response_code; char const* const new_auth_protocol; size_t const new_auth_protocol_len; size_t new_auth_protocol_data_len; scalar_t__ const server_asked_323_auth; scalar_t__ new_auth_protocol_data; int /*<<< orphan*/  error_info; int /*<<< orphan*/  charset_no; int /*<<< orphan*/  connect_attr; int /*<<< orphan*/ * auth_data; } ;
struct TYPE_41__ {char* s; } ;
struct TYPE_40__ {char* s; } ;
struct TYPE_39__ {char* s; } ;
struct TYPE_38__ {int (* get_server_version ) (TYPE_12__* const) ;scalar_t__ (* set_charset ) (TYPE_12__* const,int /*<<< orphan*/ ) ;} ;
struct TYPE_36__ {int /*<<< orphan*/  (* init_ok_packet ) (TYPE_8__*) ;int /*<<< orphan*/  (* init_auth_packet ) (TYPE_8__*) ;int /*<<< orphan*/  (* init_change_auth_response_packet ) (TYPE_8__*) ;int /*<<< orphan*/  (* init_change_user_response_packet ) (TYPE_8__*) ;} ;
struct TYPE_37__ {TYPE_2__ m; } ;
struct TYPE_35__ {scalar_t__ error_no; } ;
struct TYPE_34__ {int /*<<< orphan*/  connect_attr; } ;
struct TYPE_33__ {int /*<<< orphan*/  name; int /*<<< orphan*/  nr; } ;
struct TYPE_32__ {int server_capabilities; TYPE_25__* error_info; TYPE_4__* m; int /*<<< orphan*/  upsert_status; TYPE_7__ last_message; int /*<<< orphan*/  persistent; TYPE_6__ password; TYPE_5__ username; TYPE_3__* payload_decoder_factory; int /*<<< orphan*/  state; TYPE_13__* charset; TYPE_1__* options; } ;
typedef  TYPE_8__ MYSQLND_PACKET_OK ;
typedef  TYPE_8__ MYSQLND_PACKET_CHG_USER_RESPONSE ;
typedef  TYPE_8__ MYSQLND_PACKET_CHANGE_AUTH_RESPONSE ;
typedef  TYPE_8__ MYSQLND_PACKET_AUTH ;
typedef  TYPE_12__ MYSQLND_CONN_DATA ;
typedef  TYPE_13__ MYSQLND_CHARSET ;

/* Variables and functions */
 int CLIENT_CONNECT_ATTRS ; 
 int /*<<< orphan*/  CONN_QUIT_SENT ; 
 int /*<<< orphan*/  COPY_CLIENT_ERROR (TYPE_25__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_SERVER_GONE_ERROR ; 
 int /*<<< orphan*/  CR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,long) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PACKET_FREE (TYPE_8__*) ; 
 scalar_t__ PACKET_READ (TYPE_12__* const,TYPE_8__*) ; 
 int /*<<< orphan*/  PACKET_WRITE (TYPE_12__* const,TYPE_8__*) ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_CLIENT_ERROR (TYPE_25__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_CONNECTION_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ const TRUE ; 
 int /*<<< orphan*/  UNKNOWN_SQLSTATE ; 
 int /*<<< orphan*/  UPSERT_STATUS_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/ * mnd_emalloc (size_t) ; 
 int /*<<< orphan*/  mnd_pefree (char*,int /*<<< orphan*/ ) ; 
 char* mnd_pestrdup (char const* const,int /*<<< orphan*/ ) ; 
 char* mnd_pestrndup (char const* const,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysqlnd_old_passwd ; 
 int /*<<< orphan*/  mysqlnd_server_gone ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 scalar_t__ stub10 (TYPE_12__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*) ; 
 int stub4 (TYPE_12__* const) ; 
 long stub5 (TYPE_12__* const) ; 
 long stub6 (TYPE_12__* const) ; 
 int /*<<< orphan*/  stub7 (TYPE_8__*) ; 
 long stub8 (TYPE_12__* const) ; 
 int stub9 (TYPE_12__* const) ; 

enum_func_status
mysqlnd_auth_change_user(MYSQLND_CONN_DATA * const conn,
								const char * const user,
								const size_t user_len,
								const char * const passwd,
								const size_t passwd_len,
								const char * const db,
								const size_t db_len,
								const zend_bool silent,
								const zend_bool use_full_blown_auth_packet,
								const char * const auth_protocol,
								const zend_uchar * const auth_plugin_data,
								const size_t auth_plugin_data_len,
								char ** switch_to_auth_protocol,
								size_t * const switch_to_auth_protocol_len,
								zend_uchar ** switch_to_auth_protocol_data,
								size_t * const switch_to_auth_protocol_data_len
								)
{
	enum_func_status ret = FAIL;
	const MYSQLND_CHARSET * old_cs = conn->charset;
	MYSQLND_PACKET_CHG_USER_RESPONSE chg_user_resp;

	DBG_ENTER("mysqlnd_auth_change_user");

	conn->payload_decoder_factory->m.init_change_user_response_packet(&chg_user_resp);

	if (use_full_blown_auth_packet != TRUE) {
		MYSQLND_PACKET_CHANGE_AUTH_RESPONSE change_auth_resp_packet;

		conn->payload_decoder_factory->m.init_change_auth_response_packet(&change_auth_resp_packet);

		change_auth_resp_packet.auth_data = auth_plugin_data;
		change_auth_resp_packet.auth_data_len = auth_plugin_data_len;

		if (!PACKET_WRITE(conn, &change_auth_resp_packet)) {
			SET_CONNECTION_STATE(&conn->state, CONN_QUIT_SENT);
			SET_CLIENT_ERROR(conn->error_info, CR_SERVER_GONE_ERROR, UNKNOWN_SQLSTATE, mysqlnd_server_gone);
			PACKET_FREE(&change_auth_resp_packet);
			goto end;
		}

		PACKET_FREE(&change_auth_resp_packet);
	} else {
		MYSQLND_PACKET_AUTH auth_packet;

		conn->payload_decoder_factory->m.init_auth_packet(&auth_packet);

		auth_packet.is_change_user_packet = TRUE;
		auth_packet.user		= user;
		auth_packet.db			= db;
		auth_packet.db_len		= db_len;
		auth_packet.silent		= silent;

		auth_packet.auth_data = auth_plugin_data;
		auth_packet.auth_data_len = auth_plugin_data_len;
		auth_packet.auth_plugin_name = auth_protocol;

        if (conn->server_capabilities & CLIENT_CONNECT_ATTRS) {
			auth_packet.connect_attr = conn->options->connect_attr;
        }

		if (conn->m->get_server_version(conn) >= 50123) {
			auth_packet.charset_no	= conn->charset->nr;
		}

		if (!PACKET_WRITE(conn, &auth_packet)) {
			SET_CONNECTION_STATE(&conn->state, CONN_QUIT_SENT);
			SET_CLIENT_ERROR(conn->error_info, CR_SERVER_GONE_ERROR, UNKNOWN_SQLSTATE, mysqlnd_server_gone);
			PACKET_FREE(&auth_packet);
			goto end;
		}

		PACKET_FREE(&auth_packet);
	}

	ret = PACKET_READ(conn, &chg_user_resp);
	COPY_CLIENT_ERROR(conn->error_info, chg_user_resp.error_info);

	if (0xFE == chg_user_resp.response_code) {
		ret = FAIL;
		if (!chg_user_resp.new_auth_protocol) {
			DBG_ERR(mysqlnd_old_passwd);
			SET_CLIENT_ERROR(conn->error_info, CR_UNKNOWN_ERROR, UNKNOWN_SQLSTATE, mysqlnd_old_passwd);
		} else {
			*switch_to_auth_protocol = mnd_pestrndup(chg_user_resp.new_auth_protocol, chg_user_resp.new_auth_protocol_len, FALSE);
			*switch_to_auth_protocol_len = chg_user_resp.new_auth_protocol_len;
			if (chg_user_resp.new_auth_protocol_data) {
				*switch_to_auth_protocol_data_len = chg_user_resp.new_auth_protocol_data_len;
				*switch_to_auth_protocol_data = mnd_emalloc(*switch_to_auth_protocol_data_len);
				memcpy(*switch_to_auth_protocol_data, chg_user_resp.new_auth_protocol_data, *switch_to_auth_protocol_data_len);
			} else {
				*switch_to_auth_protocol_data = NULL;
				*switch_to_auth_protocol_data_len = 0;
			}
		}
	}

	if (conn->error_info->error_no) {
		ret = FAIL;
		/*
		  COM_CHANGE_USER is broken in 5.1. At least in 5.1.15 and 5.1.14, 5.1.11 is immune.
		  bug#25371 mysql_change_user() triggers "packets out of sync"
		  When it gets fixed, there should be one more check here
		*/
		if (conn->m->get_server_version(conn) > 50113L &&conn->m->get_server_version(conn) < 50118L) {
			MYSQLND_PACKET_OK redundant_error_packet;

			conn->payload_decoder_factory->m.init_ok_packet(&redundant_error_packet);
			PACKET_READ(conn, &redundant_error_packet);
			PACKET_FREE(&redundant_error_packet);
			DBG_INF_FMT("Server is %u, buggy, sends two ERR messages", conn->m->get_server_version(conn));
		}
	}
	if (ret == PASS) {
		char * tmp = NULL;
		/* if we get conn->username as parameter and then we first free it, then estrndup it, we will crash */
		tmp = mnd_pestrndup(user, user_len, conn->persistent);
		if (conn->username.s) {
			mnd_pefree(conn->username.s, conn->persistent);
		}
		conn->username.s = tmp;

		tmp = mnd_pestrdup(passwd, conn->persistent);
		if (conn->password.s) {
			mnd_pefree(conn->password.s, conn->persistent);
		}
		conn->password.s = tmp;

		if (conn->last_message.s) {
			mnd_pefree(conn->last_message.s, conn->persistent);
			conn->last_message.s = NULL;
		}
		UPSERT_STATUS_RESET(conn->upsert_status);
		/* set charset for old servers */
		if (conn->m->get_server_version(conn) < 50123) {
			ret = conn->m->set_charset(conn, old_cs->name);
		}
	} else if (ret == FAIL && chg_user_resp.server_asked_323_auth == TRUE) {
		/* old authentication with new server  !*/
		DBG_ERR(mysqlnd_old_passwd);
		SET_CLIENT_ERROR(conn->error_info, CR_UNKNOWN_ERROR, UNKNOWN_SQLSTATE, mysqlnd_old_passwd);
	}
end:
	PACKET_FREE(&chg_user_resp);
	DBG_RETURN(ret);
}