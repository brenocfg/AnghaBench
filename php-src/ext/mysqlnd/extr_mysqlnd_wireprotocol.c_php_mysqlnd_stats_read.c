#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  enum_func_status ;
struct TYPE_14__ {int size; } ;
struct TYPE_13__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * stats; int /*<<< orphan*/ * vio; TYPE_3__* protocol_frame_codec; int /*<<< orphan*/ * error_info; } ;
struct TYPE_10__ {char* s; size_t l; } ;
struct TYPE_12__ {TYPE_7__ header; TYPE_2__ message; } ;
struct TYPE_9__ {size_t length; scalar_t__ buffer; } ;
struct TYPE_11__ {TYPE_1__ cmd_buffer; } ;
typedef  int /*<<< orphan*/  MYSQLND_VIO ;
typedef  int /*<<< orphan*/  MYSQLND_STATS ;
typedef  TYPE_3__ MYSQLND_PFC ;
typedef  TYPE_4__ MYSQLND_PACKET_STATS ;
typedef  int /*<<< orphan*/  MYSQLND_ERROR_INFO ;
typedef  TYPE_5__ MYSQLND_CONN_DATA ;
typedef  int /*<<< orphan*/  MYSQLND_CONNECTION_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  PROT_STATS_PACKET ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 char* mnd_emalloc (int) ; 
 scalar_t__ mysqlnd_read_packet_header_and_body (TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum_func_status
php_mysqlnd_stats_read(MYSQLND_CONN_DATA * conn, void * _packet)
{
	MYSQLND_PACKET_STATS *packet= (MYSQLND_PACKET_STATS *) _packet;
	MYSQLND_ERROR_INFO * error_info = conn->error_info;
	MYSQLND_PFC * pfc = conn->protocol_frame_codec;
	MYSQLND_VIO * vio = conn->vio;
	MYSQLND_STATS * stats = conn->stats;
	MYSQLND_CONNECTION_STATE * connection_state = &conn->state;
	const size_t buf_len = pfc->cmd_buffer.length;
	zend_uchar *buf = (zend_uchar *) pfc->cmd_buffer.buffer;

	DBG_ENTER("php_mysqlnd_stats_read");

	if (FAIL == mysqlnd_read_packet_header_and_body(&(packet->header), pfc, vio, stats, error_info, connection_state, buf, buf_len, "statistics", PROT_STATS_PACKET)) {
		DBG_RETURN(FAIL);
	}

	packet->message.s = mnd_emalloc(packet->header.size + 1);
	memcpy(packet->message.s, buf, packet->header.size);
	packet->message.s[packet->header.size] = '\0';
	packet->message.l = packet->header.size;

	DBG_RETURN(PASS);
}