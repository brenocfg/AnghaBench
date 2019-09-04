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
struct rxrpc_connection {scalar_t__ active_chans; int /*<<< orphan*/  channel_lock; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 scalar_t__ RXRPC_ACTIVE_CHANS_MASK ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  rxrpc_activate_channels_locked (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  rxrpc_client_activate_chans ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_client (struct rxrpc_connection*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_activate_channels(struct rxrpc_connection *conn)
{
	_enter("%d", conn->debug_id);

	trace_rxrpc_client(conn, -1, rxrpc_client_activate_chans);

	if (conn->active_chans == RXRPC_ACTIVE_CHANS_MASK)
		return;

	spin_lock(&conn->channel_lock);
	rxrpc_activate_channels_locked(conn);
	spin_unlock(&conn->channel_lock);
	_leave("");
}