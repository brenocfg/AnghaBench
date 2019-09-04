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
struct rxrpc_net {scalar_t__ epoch; } ;
struct TYPE_4__ {scalar_t__ epoch; int cid; } ;
struct TYPE_6__ {TYPE_2__* local; } ;
struct rxrpc_connection {int /*<<< orphan*/  flags; TYPE_1__ proto; TYPE_3__ params; } ;
struct TYPE_5__ {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int RXRPC_CIDSHIFT ; 
 int /*<<< orphan*/  RXRPC_CONN_DONT_REUSE ; 
 int idr_get_cursor (int /*<<< orphan*/ *) ; 
 int max (int,unsigned int) ; 
 int /*<<< orphan*/  rxrpc_client_conn_ids ; 
 int rxrpc_max_client_connections ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rxrpc_may_reuse_conn(struct rxrpc_connection *conn)
{
	struct rxrpc_net *rxnet = conn->params.local->rxnet;
	int id_cursor, id, distance, limit;

	if (test_bit(RXRPC_CONN_DONT_REUSE, &conn->flags))
		goto dont_reuse;

	if (conn->proto.epoch != rxnet->epoch)
		goto mark_dont_reuse;

	/* The IDR tree gets very expensive on memory if the connection IDs are
	 * widely scattered throughout the number space, so we shall want to
	 * kill off connections that, say, have an ID more than about four
	 * times the maximum number of client conns away from the current
	 * allocation point to try and keep the IDs concentrated.
	 */
	id_cursor = idr_get_cursor(&rxrpc_client_conn_ids);
	id = conn->proto.cid >> RXRPC_CIDSHIFT;
	distance = id - id_cursor;
	if (distance < 0)
		distance = -distance;
	limit = max(rxrpc_max_client_connections * 4, 1024U);
	if (distance > limit)
		goto mark_dont_reuse;

	return true;

mark_dont_reuse:
	set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
dont_reuse:
	return false;
}