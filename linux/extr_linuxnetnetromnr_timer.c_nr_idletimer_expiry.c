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
struct timer_list {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; scalar_t__ sk_err; int /*<<< orphan*/  sk_state; } ;
struct nr_sock {int /*<<< orphan*/  state; scalar_t__ n2count; struct sock sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_DISCREQ ; 
 int /*<<< orphan*/  NR_STATE_2 ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct nr_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idletimer ; 
 struct nr_sock* nr ; 
 int /*<<< orphan*/  nr_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t2timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t4timer (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void nr_idletimer_expiry(struct timer_list *t)
{
	struct nr_sock *nr = from_timer(nr, t, idletimer);
	struct sock *sk = &nr->sock;

	bh_lock_sock(sk);

	nr_clear_queues(sk);

	nr->n2count = 0;
	nr_write_internal(sk, NR_DISCREQ);
	nr->state = NR_STATE_2;

	nr_start_t1timer(sk);
	nr_stop_t2timer(sk);
	nr_stop_t4timer(sk);

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = 0;
	sk->sk_shutdown |= SEND_SHUTDOWN;

	if (!sock_flag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	}
	bh_unlock_sock(sk);
}