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
struct vsock_sock {struct hvsock* trans; } ;
struct vmbus_channel {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct hvsock {struct vmbus_channel* chan; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  TCP_CLOSING ; 
 int /*<<< orphan*/  hvs_shutdown (struct vsock_sock*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_sock (struct vsock_sock*) ; 

__attribute__((used)) static void hvs_release(struct vsock_sock *vsk)
{
	struct sock *sk = sk_vsock(vsk);
	struct hvsock *hvs = vsk->trans;
	struct vmbus_channel *chan;

	lock_sock(sk);

	sk->sk_state = TCP_CLOSING;
	vsock_remove_sock(vsk);

	release_sock(sk);

	chan = hvs->chan;
	if (chan)
		hvs_shutdown(vsk, RCV_SHUTDOWN | SEND_SHUTDOWN);

}