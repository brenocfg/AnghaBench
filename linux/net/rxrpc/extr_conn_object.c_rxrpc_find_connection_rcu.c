#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_27__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_28__ {TYPE_8__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_19__ {int family; TYPE_13__ sin6; TYPE_9__ sin; } ;
struct sockaddr_rxrpc {TYPE_14__ transport; } ;
struct sk_buff {int dummy; } ;
struct TYPE_22__ {int cid; scalar_t__ epoch; } ;
struct rxrpc_skb_priv {TYPE_3__ hdr; } ;
struct TYPE_15__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_25__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_26__ {TYPE_6__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_16__ {TYPE_10__ sin6; TYPE_7__ sin; } ;
struct TYPE_17__ {TYPE_11__ transport; } ;
struct rxrpc_peer {TYPE_12__ srx; } ;
struct TYPE_20__ {int family; } ;
struct TYPE_21__ {TYPE_1__ transport; } ;
struct rxrpc_local {TYPE_2__ srx; } ;
struct TYPE_24__ {struct rxrpc_peer* peer; struct rxrpc_local* local; } ;
struct TYPE_23__ {scalar_t__ epoch; } ;
struct rxrpc_connection {TYPE_5__ params; TYPE_4__ proto; int /*<<< orphan*/  usage; } ;
struct rxrpc_conn_proto {scalar_t__ epoch; int cid; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  BUG () ; 
 int RXRPC_CIDMASK ; 
 int RXRPC_CIDSHIFT ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct rxrpc_connection* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int,int) ; 
 int /*<<< orphan*/  rxrpc_client_conn_ids ; 
 scalar_t__ rxrpc_extract_addr_from_skb (struct sockaddr_rxrpc*,struct sk_buff*) ; 
 struct rxrpc_connection* rxrpc_find_service_conn_rcu (struct rxrpc_peer*,struct sk_buff*) ; 
 struct rxrpc_peer* rxrpc_lookup_peer_rcu (struct rxrpc_local*,struct sockaddr_rxrpc*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 scalar_t__ rxrpc_to_server (struct rxrpc_skb_priv*) ; 

struct rxrpc_connection *rxrpc_find_connection_rcu(struct rxrpc_local *local,
						   struct sk_buff *skb,
						   struct rxrpc_peer **_peer)
{
	struct rxrpc_connection *conn;
	struct rxrpc_conn_proto k;
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	struct sockaddr_rxrpc srx;
	struct rxrpc_peer *peer;

	_enter(",%x", sp->hdr.cid & RXRPC_CIDMASK);

	if (rxrpc_extract_addr_from_skb(&srx, skb) < 0)
		goto not_found;

	if (srx.transport.family != local->srx.transport.family &&
	    (srx.transport.family == AF_INET &&
	     local->srx.transport.family != AF_INET6)) {
		pr_warn_ratelimited("AF_RXRPC: Protocol mismatch %u not %u\n",
				    srx.transport.family,
				    local->srx.transport.family);
		goto not_found;
	}

	k.epoch	= sp->hdr.epoch;
	k.cid	= sp->hdr.cid & RXRPC_CIDMASK;

	if (rxrpc_to_server(sp)) {
		/* We need to look up service connections by the full protocol
		 * parameter set.  We look up the peer first as an intermediate
		 * step and then the connection from the peer's tree.
		 */
		peer = rxrpc_lookup_peer_rcu(local, &srx);
		if (!peer)
			goto not_found;
		*_peer = peer;
		conn = rxrpc_find_service_conn_rcu(peer, skb);
		if (!conn || atomic_read(&conn->usage) == 0)
			goto not_found;
		_leave(" = %p", conn);
		return conn;
	} else {
		/* Look up client connections by connection ID alone as their
		 * IDs are unique for this machine.
		 */
		conn = idr_find(&rxrpc_client_conn_ids,
				sp->hdr.cid >> RXRPC_CIDSHIFT);
		if (!conn || atomic_read(&conn->usage) == 0) {
			_debug("no conn");
			goto not_found;
		}

		if (conn->proto.epoch != k.epoch ||
		    conn->params.local != local)
			goto not_found;

		peer = conn->params.peer;
		switch (srx.transport.family) {
		case AF_INET:
			if (peer->srx.transport.sin.sin_port !=
			    srx.transport.sin.sin_port ||
			    peer->srx.transport.sin.sin_addr.s_addr !=
			    srx.transport.sin.sin_addr.s_addr)
				goto not_found;
			break;
#ifdef CONFIG_AF_RXRPC_IPV6
		case AF_INET6:
			if (peer->srx.transport.sin6.sin6_port !=
			    srx.transport.sin6.sin6_port ||
			    memcmp(&peer->srx.transport.sin6.sin6_addr,
				   &srx.transport.sin6.sin6_addr,
				   sizeof(struct in6_addr)) != 0)
				goto not_found;
			break;
#endif
		default:
			BUG();
		}

		_leave(" = %p", conn);
		return conn;
	}

not_found:
	_leave(" = NULL");
	return NULL;
}