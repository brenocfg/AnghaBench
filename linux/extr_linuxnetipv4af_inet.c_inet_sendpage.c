#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {TYPE_1__* sk_prot; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  inet_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sendpage ) (struct sock*,struct page*,int,size_t,int) ;int /*<<< orphan*/  no_autobind; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ inet_autobind (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_no_sendpage (struct socket*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  sock_rps_record_flow (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct page*,int,size_t,int) ; 

ssize_t inet_sendpage(struct socket *sock, struct page *page, int offset,
		      size_t size, int flags)
{
	struct sock *sk = sock->sk;

	sock_rps_record_flow(sk);

	/* We may need to bind the socket. */
	if (!inet_sk(sk)->inet_num && !sk->sk_prot->no_autobind &&
	    inet_autobind(sk))
		return -EAGAIN;

	if (sk->sk_prot->sendpage)
		return sk->sk_prot->sendpage(sk, page, offset, size, flags);
	return sock_no_sendpage(sock, page, offset, size, flags);
}