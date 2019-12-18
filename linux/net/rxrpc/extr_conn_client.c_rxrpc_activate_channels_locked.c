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
typedef  int u8 ;
struct rxrpc_connection {int cache_state; int active_chans; int /*<<< orphan*/  waiting_calls; } ;

/* Variables and functions */
 int RXRPC_ACTIVE_CHANS_MASK ; 
#define  RXRPC_CONN_CLIENT_ACTIVE 129 
#define  RXRPC_CONN_CLIENT_UPGRADE 128 
 int /*<<< orphan*/  __ffs (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_activate_one_channel (struct rxrpc_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_activate_channels_locked(struct rxrpc_connection *conn)
{
	u8 avail, mask;

	switch (conn->cache_state) {
	case RXRPC_CONN_CLIENT_ACTIVE:
		mask = RXRPC_ACTIVE_CHANS_MASK;
		break;
	case RXRPC_CONN_CLIENT_UPGRADE:
		mask = 0x01;
		break;
	default:
		return;
	}

	while (!list_empty(&conn->waiting_calls) &&
	       (avail = ~conn->active_chans,
		avail &= mask,
		avail != 0))
		rxrpc_activate_one_channel(conn, __ffs(avail));
}