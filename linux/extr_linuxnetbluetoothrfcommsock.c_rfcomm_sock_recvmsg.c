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
struct socket {struct sock* sk; } ;
struct sock {int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct rfcomm_dlc {int /*<<< orphan*/  flags; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int MSG_PEEK ; 
 int /*<<< orphan*/  RFCOMM_DEFER_SETUP ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int bt_sock_stream_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_dlc_accept (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unthrottle (struct rfcomm_dlc*) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_sock_recvmsg(struct socket *sock, struct msghdr *msg,
			       size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct rfcomm_dlc *d = rfcomm_pi(sk)->dlc;
	int len;

	if (test_and_clear_bit(RFCOMM_DEFER_SETUP, &d->flags)) {
		rfcomm_dlc_accept(d);
		return 0;
	}

	len = bt_sock_stream_recvmsg(sock, msg, size, flags);

	lock_sock(sk);
	if (!(flags & MSG_PEEK) && len > 0)
		atomic_sub(len, &sk->sk_rmem_alloc);

	if (atomic_read(&sk->sk_rmem_alloc) <= (sk->sk_rcvbuf >> 2))
		rfcomm_dlc_unthrottle(rfcomm_pi(sk)->dlc);
	release_sock(sk);

	return len;
}