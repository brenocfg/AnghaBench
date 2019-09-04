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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct pppol2tp_session {int /*<<< orphan*/  rcu; int /*<<< orphan*/  sk_lock; int /*<<< orphan*/  sk; int /*<<< orphan*/  __sk; } ;
struct l2tp_session {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  PPPOX_DEAD ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_session_delete (struct l2tp_session*) ; 
 struct pppol2tp_session* l2tp_session_priv (struct l2tp_session*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pppol2tp_put_sk ; 
 struct l2tp_session* pppol2tp_sock_to_session (struct sock*) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int pppol2tp_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct l2tp_session *session;
	int error;

	if (!sk)
		return 0;

	error = -EBADF;
	lock_sock(sk);
	if (sock_flag(sk, SOCK_DEAD) != 0)
		goto error;

	pppox_unbind_sock(sk);

	/* Signal the death of the socket. */
	sk->sk_state = PPPOX_DEAD;
	sock_orphan(sk);
	sock->sk = NULL;

	session = pppol2tp_sock_to_session(sk);
	if (session) {
		struct pppol2tp_session *ps;

		l2tp_session_delete(session);

		ps = l2tp_session_priv(session);
		mutex_lock(&ps->sk_lock);
		ps->__sk = rcu_dereference_protected(ps->sk,
						     lockdep_is_held(&ps->sk_lock));
		RCU_INIT_POINTER(ps->sk, NULL);
		mutex_unlock(&ps->sk_lock);
		call_rcu(&ps->rcu, pppol2tp_put_sk);

		/* Rely on the sock_put() call at the end of the function for
		 * dropping the reference held by pppol2tp_sock_to_session().
		 * The last reference will be dropped by pppol2tp_put_sk().
		 */
	}

	release_sock(sk);

	/* This will delete the session context via
	 * pppol2tp_session_destruct() if the socket's refcnt drops to
	 * zero.
	 */
	sock_put(sk);

	return 0;

error:
	release_sock(sk);
	return error;
}