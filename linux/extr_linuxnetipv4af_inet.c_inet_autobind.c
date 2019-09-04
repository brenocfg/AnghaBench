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
struct sock {TYPE_1__* sk_prot; } ;
struct inet_sock {int /*<<< orphan*/  inet_num; int /*<<< orphan*/  inet_sport; } ;
struct TYPE_2__ {scalar_t__ (* get_port ) (struct sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ stub1 (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_autobind(struct sock *sk)
{
	struct inet_sock *inet;
	/* We may need to bind the socket. */
	lock_sock(sk);
	inet = inet_sk(sk);
	if (!inet->inet_num) {
		if (sk->sk_prot->get_port(sk, 0)) {
			release_sock(sk);
			return -EAGAIN;
		}
		inet->inet_sport = htons(inet->inet_num);
	}
	release_sock(sk);
	return 0;
}