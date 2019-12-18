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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;
struct nr_sock {int state; int /*<<< orphan*/  n2count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_DISCREQ ; 
#define  NR_STATE_0 131 
#define  NR_STATE_1 130 
#define  NR_STATE_2 129 
#define  NR_STATE_3 128 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  nr_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  nr_destroy_socket (struct sock*) ; 
 int /*<<< orphan*/  nr_disconnect (struct sock*,int /*<<< orphan*/ ) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t2timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t4timer (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int nr_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct nr_sock *nr;

	if (sk == NULL) return 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	nr = nr_sk(sk);

	switch (nr->state) {
	case NR_STATE_0:
	case NR_STATE_1:
	case NR_STATE_2:
		nr_disconnect(sk, 0);
		nr_destroy_socket(sk);
		break;

	case NR_STATE_3:
		nr_clear_queues(sk);
		nr->n2count = 0;
		nr_write_internal(sk, NR_DISCREQ);
		nr_start_t1timer(sk);
		nr_stop_t2timer(sk);
		nr_stop_t4timer(sk);
		nr_stop_idletimer(sk);
		nr->state    = NR_STATE_2;
		sk->sk_state    = TCP_CLOSE;
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DESTROY);
		break;

	default:
		break;
	}

	sock->sk   = NULL;
	release_sock(sk);
	sock_put(sk);

	return 0;
}