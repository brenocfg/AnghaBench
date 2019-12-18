#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cid; } ;
struct rxrpc_connection {TYPE_1__ proto; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int RXRPC_CIDSHIFT ; 
 int /*<<< orphan*/  RXRPC_CONN_HAS_IDR ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rxrpc_client_conn_ids ; 
 int /*<<< orphan*/  rxrpc_conn_id_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_put_client_connection_id(struct rxrpc_connection *conn)
{
	if (test_bit(RXRPC_CONN_HAS_IDR, &conn->flags)) {
		spin_lock(&rxrpc_conn_id_lock);
		idr_remove(&rxrpc_client_conn_ids,
			   conn->proto.cid >> RXRPC_CIDSHIFT);
		spin_unlock(&rxrpc_conn_id_lock);
	}
}