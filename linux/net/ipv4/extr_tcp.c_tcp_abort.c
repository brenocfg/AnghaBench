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
struct sock {scalar_t__ sk_state; int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;
struct request_sock {int /*<<< orphan*/  rsk_listener; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ TCP_NEW_SYN_RECV ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_listen_stop (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (int /*<<< orphan*/ ,struct request_sock*) ; 
 struct request_sock* inet_reqsk (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 scalar_t__ tcp_need_reset (scalar_t__) ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 

int tcp_abort(struct sock *sk, int err)
{
	if (!sk_fullsock(sk)) {
		if (sk->sk_state == TCP_NEW_SYN_RECV) {
			struct request_sock *req = inet_reqsk(sk);

			local_bh_disable();
			inet_csk_reqsk_queue_drop(req->rsk_listener, req);
			local_bh_enable();
			return 0;
		}
		return -EOPNOTSUPP;
	}

	/* Don't race with userspace socket closes such as tcp_close. */
	lock_sock(sk);

	if (sk->sk_state == TCP_LISTEN) {
		tcp_set_state(sk, TCP_CLOSE);
		inet_csk_listen_stop(sk);
	}

	/* Don't race with BH socket closes such as inet_csk_listen_stop. */
	local_bh_disable();
	bh_lock_sock(sk);

	if (!sock_flag(sk, SOCK_DEAD)) {
		sk->sk_err = err;
		/* This barrier is coupled with smp_rmb() in tcp_poll() */
		smp_wmb();
		sk->sk_error_report(sk);
		if (tcp_need_reset(sk->sk_state))
			tcp_send_active_reset(sk, GFP_ATOMIC);
		tcp_done(sk);
	}

	bh_unlock_sock(sk);
	local_bh_enable();
	tcp_write_queue_purge(sk);
	release_sock(sk);
	return 0;
}