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
struct vsock_sock {int close_work_scheduled; int /*<<< orphan*/  close_work; int /*<<< orphan*/  peer_shutdown; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  TCP_CLOSING ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  vsock_remove_sock (struct vsock_sock*) ; 
 scalar_t__ vsock_stream_has_data (struct vsock_sock*) ; 

__attribute__((used)) static void virtio_transport_do_close(struct vsock_sock *vsk,
				      bool cancel_timeout)
{
	struct sock *sk = sk_vsock(vsk);

	sock_set_flag(sk, SOCK_DONE);
	vsk->peer_shutdown = SHUTDOWN_MASK;
	if (vsock_stream_has_data(vsk) <= 0)
		sk->sk_state = TCP_CLOSING;
	sk->sk_state_change(sk);

	if (vsk->close_work_scheduled &&
	    (!cancel_timeout || cancel_delayed_work(&vsk->close_work))) {
		vsk->close_work_scheduled = false;

		vsock_remove_sock(vsk);

		/* Release refcnt obtained when we scheduled the timeout */
		sock_put(sk);
	}
}