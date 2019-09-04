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
struct sock {scalar_t__ sk_type; } ;
struct vsock_sock {struct sock sk; } ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int virtio_transport_close (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_sock (struct vsock_sock*) ; 

void virtio_transport_release(struct vsock_sock *vsk)
{
	struct sock *sk = &vsk->sk;
	bool remove_sock = true;

	lock_sock(sk);
	if (sk->sk_type == SOCK_STREAM)
		remove_sock = virtio_transport_close(vsk);
	release_sock(sk);

	if (remove_sock)
		vsock_remove_sock(vsk);
}