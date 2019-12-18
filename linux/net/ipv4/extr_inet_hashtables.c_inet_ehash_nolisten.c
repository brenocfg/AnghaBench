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
struct TYPE_2__ {int /*<<< orphan*/  orphan_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  inet_csk_destroy_sock (struct sock*) ; 
 int inet_ehash_insert (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  inet_sk_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

bool inet_ehash_nolisten(struct sock *sk, struct sock *osk)
{
	bool ok = inet_ehash_insert(sk, osk);

	if (ok) {
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	} else {
		percpu_counter_inc(sk->sk_prot->orphan_count);
		inet_sk_set_state(sk, TCP_CLOSE);
		sock_set_flag(sk, SOCK_DEAD);
		inet_csk_destroy_sock(sk);
	}
	return ok;
}