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
struct sock {int dummy; } ;
struct pppol2tp_session {int /*<<< orphan*/  sk; } ;
struct l2tp_session {int dummy; } ;

/* Variables and functions */
 struct pppol2tp_session* l2tp_session_priv (struct l2tp_session*) ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static struct sock *pppol2tp_session_get_sock(struct l2tp_session *session)
{
	struct pppol2tp_session *ps = l2tp_session_priv(session);
	struct sock *sk;

	rcu_read_lock();
	sk = rcu_dereference(ps->sk);
	if (sk)
		sock_hold(sk);
	rcu_read_unlock();

	return sk;
}