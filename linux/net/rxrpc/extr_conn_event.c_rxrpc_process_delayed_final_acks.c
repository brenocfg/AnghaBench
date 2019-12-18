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
struct rxrpc_connection {int /*<<< orphan*/  flags; struct rxrpc_channel* channels; } ;
struct rxrpc_channel {int /*<<< orphan*/  final_ack_at; } ;

/* Variables and functions */
 unsigned long LONG_MAX ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ RXRPC_CONN_FINAL_ACK_0 ; 
 unsigned int RXRPC_MAXCALLS ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_conn_retransmit_call (struct rxrpc_connection*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rxrpc_reduce_conn_timer (struct rxrpc_connection*,unsigned long) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_and_clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void rxrpc_process_delayed_final_acks(struct rxrpc_connection *conn)
{
	unsigned long j = jiffies, next_j;
	unsigned int channel;
	bool set;

again:
	next_j = j + LONG_MAX;
	set = false;
	for (channel = 0; channel < RXRPC_MAXCALLS; channel++) {
		struct rxrpc_channel *chan = &conn->channels[channel];
		unsigned long ack_at;

		if (!test_bit(RXRPC_CONN_FINAL_ACK_0 + channel, &conn->flags))
			continue;

		smp_rmb(); /* vs rxrpc_disconnect_client_call */
		ack_at = READ_ONCE(chan->final_ack_at);

		if (time_before(j, ack_at)) {
			if (time_before(ack_at, next_j)) {
				next_j = ack_at;
				set = true;
			}
			continue;
		}

		if (test_and_clear_bit(RXRPC_CONN_FINAL_ACK_0 + channel,
				       &conn->flags))
			rxrpc_conn_retransmit_call(conn, NULL, channel);
	}

	j = jiffies;
	if (time_before_eq(next_j, j))
		goto again;
	if (set)
		rxrpc_reduce_conn_timer(conn, next_j);
}