#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rxrpc_net {int /*<<< orphan*/  epoch; } ;
struct TYPE_4__ {int cid; int /*<<< orphan*/  epoch; } ;
struct TYPE_5__ {TYPE_3__* local; } ;
struct rxrpc_connection {TYPE_1__ proto; int /*<<< orphan*/  flags; TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int RXRPC_CIDSHIFT ; 
 int /*<<< orphan*/  RXRPC_CONN_HAS_IDR ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct rxrpc_connection*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  rxrpc_client_conn_ids ; 
 int /*<<< orphan*/  rxrpc_conn_id_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_get_client_connection_id(struct rxrpc_connection *conn,
					  gfp_t gfp)
{
	struct rxrpc_net *rxnet = conn->params.local->rxnet;
	int id;

	_enter("");

	idr_preload(gfp);
	spin_lock(&rxrpc_conn_id_lock);

	id = idr_alloc_cyclic(&rxrpc_client_conn_ids, conn,
			      1, 0x40000000, GFP_NOWAIT);
	if (id < 0)
		goto error;

	spin_unlock(&rxrpc_conn_id_lock);
	idr_preload_end();

	conn->proto.epoch = rxnet->epoch;
	conn->proto.cid = id << RXRPC_CIDSHIFT;
	set_bit(RXRPC_CONN_HAS_IDR, &conn->flags);
	_leave(" [CID %x]", conn->proto.cid);
	return 0;

error:
	spin_unlock(&rxrpc_conn_id_lock);
	idr_preload_end();
	_leave(" = %d", id);
	return id;
}