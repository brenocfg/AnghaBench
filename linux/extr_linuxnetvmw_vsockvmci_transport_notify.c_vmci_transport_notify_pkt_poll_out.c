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
struct vsock_sock {int dummy; } ;
struct sock {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  send_waiting_write (struct sock*,int) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 scalar_t__ vsock_stream_has_space (struct vsock_sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_poll_out(struct sock *sk,
				   size_t target, bool *space_avail_now)
{
	s64 produce_q_free_space;
	struct vsock_sock *vsk = vsock_sk(sk);

	produce_q_free_space = vsock_stream_has_space(vsk);
	if (produce_q_free_space > 0) {
		*space_avail_now = true;
		return 0;
	} else if (produce_q_free_space == 0) {
		/* This is a connected socket but we can't currently send data.
		 * Notify the peer that we are waiting if the queue is full. We
		 * only send a waiting write if the queue is full because
		 * otherwise we end up in an infinite WAITING_WRITE, READ,
		 * WAITING_WRITE, READ, etc. loop. Treat failing to send the
		 * notification as a socket error, passing that back through
		 * the mask.
		 */
		if (!send_waiting_write(sk, 1))
			return -1;

		*space_avail_now = false;
	}

	return 0;
}