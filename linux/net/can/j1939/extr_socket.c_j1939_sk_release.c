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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa; int /*<<< orphan*/  src_name; } ;
struct j1939_sock {int state; int /*<<< orphan*/  filters; TYPE_1__ addr; int /*<<< orphan*/  sk; int /*<<< orphan*/  waitq; struct j1939_priv* priv; } ;
struct j1939_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int J1939_SOCK_BOUND ; 
 int /*<<< orphan*/  j1939_cancel_active_session (struct j1939_priv*,struct sock*) ; 
 int /*<<< orphan*/  j1939_jsk_del (struct j1939_priv*,struct j1939_sock*) ; 
 int /*<<< orphan*/  j1939_local_ecu_put (struct j1939_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_netdev_stop (struct j1939_priv*) ; 
 struct j1939_sock* j1939_sk (struct sock*) ; 
 int /*<<< orphan*/  j1939_sk_queue_drop_all (struct j1939_priv*,struct j1939_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_sock_pending_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int j1939_sk_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct j1939_sock *jsk;

	if (!sk)
		return 0;

	jsk = j1939_sk(sk);
	lock_sock(sk);

	if (jsk->state & J1939_SOCK_BOUND) {
		struct j1939_priv *priv = jsk->priv;

		if (wait_event_interruptible(jsk->waitq,
					     !j1939_sock_pending_get(&jsk->sk))) {
			j1939_cancel_active_session(priv, sk);
			j1939_sk_queue_drop_all(priv, jsk, ESHUTDOWN);
		}

		j1939_jsk_del(priv, jsk);

		j1939_local_ecu_put(priv, jsk->addr.src_name,
				    jsk->addr.sa);

		j1939_netdev_stop(priv);
	}

	kfree(jsk->filters);
	sock_orphan(sk);
	sock->sk = NULL;

	release_sock(sk);
	sock_put(sk);

	return 0;
}