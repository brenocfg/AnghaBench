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
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  vsock_block_update_write_window (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 scalar_t__ vsock_stream_has_data (struct vsock_sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_poll_in(struct sock *sk,
				  size_t target, bool *data_ready_now)
{
	struct vsock_sock *vsk = vsock_sk(sk);

	if (vsock_stream_has_data(vsk)) {
		*data_ready_now = true;
	} else {
		/* We can't read right now because there is nothing in the
		 * queue. Ask for notifications when there is something to
		 * read.
		 */
		if (sk->sk_state == TCP_ESTABLISHED)
			vsock_block_update_write_window(sk);
		*data_ready_now = false;
	}

	return 0;
}