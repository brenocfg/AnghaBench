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
struct sock {void (* sk_user_data ) (struct sock*) ;void (* sk_data_ready ) (struct sock*) ;scalar_t__ sk_state; int /*<<< orphan*/  sk_callback_lock; } ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  o2net_listen_work ; 
 int /*<<< orphan*/  o2net_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_listen_data_ready(struct sock *sk)
{
	void (*ready)(struct sock *sk);

	read_lock_bh(&sk->sk_callback_lock);
	ready = sk->sk_user_data;
	if (ready == NULL) { /* check for teardown race */
		ready = sk->sk_data_ready;
		goto out;
	}

	/* This callback may called twice when a new connection
	 * is  being established as a child socket inherits everything
	 * from a parent LISTEN socket, including the data_ready cb of
	 * the parent. This leads to a hazard. In o2net_accept_one()
	 * we are still initializing the child socket but have not
	 * changed the inherited data_ready callback yet when
	 * data starts arriving.
	 * We avoid this hazard by checking the state.
	 * For the listening socket,  the state will be TCP_LISTEN; for the new
	 * socket, will be  TCP_ESTABLISHED. Also, in this case,
	 * sk->sk_user_data is not a valid function pointer.
	 */

	if (sk->sk_state == TCP_LISTEN) {
		queue_work(o2net_wq, &o2net_listen_work);
	} else {
		ready = NULL;
	}

out:
	read_unlock_bh(&sk->sk_callback_lock);
	if (ready != NULL)
		ready(sk);
}