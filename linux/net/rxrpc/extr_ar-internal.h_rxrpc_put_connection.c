#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rxrpc_connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ rxrpc_conn_is_client (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  rxrpc_put_client_conn (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  rxrpc_put_service_conn (struct rxrpc_connection*) ; 

__attribute__((used)) static inline void rxrpc_put_connection(struct rxrpc_connection *conn)
{
	if (!conn)
		return;

	if (rxrpc_conn_is_client(conn))
		rxrpc_put_client_conn(conn);
	else
		rxrpc_put_service_conn(conn);
}