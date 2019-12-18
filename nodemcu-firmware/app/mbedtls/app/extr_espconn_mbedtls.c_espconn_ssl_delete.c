#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* tcp; } ;
struct espconn {scalar_t__ link_cnt; TYPE_2__ proto; } ;
typedef  int /*<<< orphan*/  sint8 ;
typedef  int /*<<< orphan*/  remot_info ;
typedef  TYPE_3__* pmbedtls_msg ;
struct TYPE_11__ {TYPE_3__* pssl; struct espconn* preverse; } ;
typedef  TYPE_4__ espconn_msg ;
struct TYPE_10__ {int /*<<< orphan*/  listen_fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPCONN_ARG ; 
 int /*<<< orphan*/  ESPCONN_INPROGRESS ; 
 int /*<<< orphan*/  ESPCONN_OK ; 
 int /*<<< orphan*/  ESPCONN_SSL ; 
 int /*<<< orphan*/  def_certificate ; 
 int /*<<< orphan*/  def_private_key ; 
 int /*<<< orphan*/  espconn_get_connection_info (struct espconn*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_kill_pcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_msg_free (TYPE_3__**) ; 
 int /*<<< orphan*/  mbedtls_net_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_parame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (TYPE_4__*) ; 
 TYPE_4__* plink_server ; 

sint8  espconn_ssl_delete(struct espconn *pdeletecon)
{
	remot_info *pinfo = NULL;
	espconn_msg *pdelete_msg = NULL;
	pmbedtls_msg mbedTLSMsg = NULL;

	if (pdeletecon == NULL)
		return ESPCONN_ARG;

	espconn_get_connection_info(pdeletecon, &pinfo, ESPCONN_SSL);
	/*make sure all the active connection have been disconnect*/
	if (pdeletecon->link_cnt != 0)
		return ESPCONN_INPROGRESS;
	else {
		pdelete_msg = plink_server;
		if (pdelete_msg != NULL && pdelete_msg->preverse == pdeletecon) {
			mbedTLSMsg = pdelete_msg->pssl;
			espconn_kill_pcb(pdeletecon->proto.tcp->local_port);
			mbedtls_net_free(&mbedTLSMsg->listen_fd);
			mbedtls_msg_free(&mbedTLSMsg);
			pdelete_msg->pssl = mbedTLSMsg;
			os_free(pdelete_msg);
			pdelete_msg = NULL;
			plink_server = pdelete_msg;
			mbedtls_parame_free(&def_private_key);
			mbedtls_parame_free(&def_certificate);
			return ESPCONN_OK;
		} else {
			return ESPCONN_ARG;
		}
	}
}