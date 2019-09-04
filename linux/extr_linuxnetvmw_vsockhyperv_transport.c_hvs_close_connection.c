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
struct vsock_sock {int peer_shutdown; } ;
struct vmbus_channel {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 struct sock* get_per_channel_state (struct vmbus_channel*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void hvs_close_connection(struct vmbus_channel *chan)
{
	struct sock *sk = get_per_channel_state(chan);
	struct vsock_sock *vsk = vsock_sk(sk);

	lock_sock(sk);

	sk->sk_state = TCP_CLOSE;
	sock_set_flag(sk, SOCK_DONE);
	vsk->peer_shutdown |= SEND_SHUTDOWN | RCV_SHUTDOWN;

	sk->sk_state_change(sk);

	release_sock(sk);
}