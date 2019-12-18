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
struct sock {scalar_t__ sk_state; int sk_shutdown; int /*<<< orphan*/  sk_lingertime; } ;
struct vsock_sock {int peer_shutdown; int close_work_scheduled; int /*<<< orphan*/  close_work; struct sock sk; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PF_EXITING ; 
 int SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  SOCK_LINGER ; 
 scalar_t__ TCP_CLOSING ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  VSOCK_CLOSE_TIMEOUT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  virtio_transport_close_timeout ; 
 int /*<<< orphan*/  virtio_transport_reset (struct vsock_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_transport_shutdown (struct vsock_sock*,int) ; 
 int /*<<< orphan*/  virtio_transport_wait_close (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool virtio_transport_close(struct vsock_sock *vsk)
{
	struct sock *sk = &vsk->sk;

	if (!(sk->sk_state == TCP_ESTABLISHED ||
	      sk->sk_state == TCP_CLOSING))
		return true;

	/* Already received SHUTDOWN from peer, reply with RST */
	if ((vsk->peer_shutdown & SHUTDOWN_MASK) == SHUTDOWN_MASK) {
		(void)virtio_transport_reset(vsk, NULL);
		return true;
	}

	if ((sk->sk_shutdown & SHUTDOWN_MASK) != SHUTDOWN_MASK)
		(void)virtio_transport_shutdown(vsk, SHUTDOWN_MASK);

	if (sock_flag(sk, SOCK_LINGER) && !(current->flags & PF_EXITING))
		virtio_transport_wait_close(sk, sk->sk_lingertime);

	if (sock_flag(sk, SOCK_DONE)) {
		return true;
	}

	sock_hold(sk);
	INIT_DELAYED_WORK(&vsk->close_work,
			  virtio_transport_close_timeout);
	vsk->close_work_scheduled = true;
	schedule_delayed_work(&vsk->close_work, VSOCK_CLOSE_TIMEOUT);
	return false;
}