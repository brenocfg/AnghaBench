#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ from; scalar_t__ to; } ;
struct rxrpc_sock {TYPE_2__ service_upgrade; } ;
struct TYPE_5__ {int cid; scalar_t__ serviceId; scalar_t__ userStatus; int /*<<< orphan*/  securityIndex; int /*<<< orphan*/  epoch; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct TYPE_8__ {int cid; int /*<<< orphan*/  epoch; } ;
struct TYPE_7__ {scalar_t__ service_id; int /*<<< orphan*/  peer; } ;
struct rxrpc_connection {scalar_t__ service_id; TYPE_4__ proto; int /*<<< orphan*/  debug_id; TYPE_3__ params; int /*<<< orphan*/  state; int /*<<< orphan*/  security_ix; scalar_t__ out_clientflag; } ;

/* Variables and functions */
 int RXRPC_CIDMASK ; 
 int /*<<< orphan*/  RXRPC_CONN_SERVICE ; 
 int /*<<< orphan*/  RXRPC_CONN_SERVICE_UNSECURED ; 
 scalar_t__ RXRPC_USERSTATUS_SERVICE_UPGRADE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _net (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rxrpc_publish_service_conn (int /*<<< orphan*/ ,struct rxrpc_connection*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 

void rxrpc_new_incoming_connection(struct rxrpc_sock *rx,
				   struct rxrpc_connection *conn,
				   struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);

	_enter("");

	conn->proto.epoch	= sp->hdr.epoch;
	conn->proto.cid		= sp->hdr.cid & RXRPC_CIDMASK;
	conn->params.service_id	= sp->hdr.serviceId;
	conn->service_id	= sp->hdr.serviceId;
	conn->security_ix	= sp->hdr.securityIndex;
	conn->out_clientflag	= 0;
	if (conn->security_ix)
		conn->state	= RXRPC_CONN_SERVICE_UNSECURED;
	else
		conn->state	= RXRPC_CONN_SERVICE;

	/* See if we should upgrade the service.  This can only happen on the
	 * first packet on a new connection.  Once done, it applies to all
	 * subsequent calls on that connection.
	 */
	if (sp->hdr.userStatus == RXRPC_USERSTATUS_SERVICE_UPGRADE &&
	    conn->service_id == rx->service_upgrade.from)
		conn->service_id = rx->service_upgrade.to;

	/* Make the connection a target for incoming packets. */
	rxrpc_publish_service_conn(conn->params.peer, conn);

	_net("CONNECTION new %d {%x}", conn->debug_id, conn->proto.cid);
}