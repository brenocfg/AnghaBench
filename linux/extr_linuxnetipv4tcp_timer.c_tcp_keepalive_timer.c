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
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct tcp_sock {scalar_t__ linger2; scalar_t__ packets_out; } ;
struct sock {int sk_state; } ;
struct inet_connection_sock {scalar_t__ icsk_user_timeout; scalar_t__ icsk_probes_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  LINUX_MIB_TCPKEEPALIVE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 int TCPF_CLOSE ; 
 int TCPF_SYN_SENT ; 
 int TCP_FIN_WAIT2 ; 
 int TCP_LISTEN ; 
 int TCP_RESOURCE_PROBE_INTERVAL ; 
 int TCP_TIMEWAIT_LEN ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock*,int) ; 
 int keepalive_intvl_when (struct tcp_sock*) ; 
 scalar_t__ keepalive_probes (struct tcp_sock*) ; 
 int keepalive_time_elapsed (struct tcp_sock*) ; 
 int keepalive_time_when (struct tcp_sock*) ; 
 int msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  sk_timer ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int tcp_fin_time (struct sock*) ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_wait (struct sock*,int,int const) ; 
 int /*<<< orphan*/  tcp_write_err (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_empty (struct sock*) ; 
 scalar_t__ tcp_write_wakeup (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_keepalive_timer (struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	u32 elapsed;

	/* Only process if socket is not in use. */
	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) {
		/* Try again later. */
		inet_csk_reset_keepalive_timer (sk, HZ/20);
		goto out;
	}

	if (sk->sk_state == TCP_LISTEN) {
		pr_err("Hmm... keepalive on a LISTEN ???\n");
		goto out;
	}

	tcp_mstamp_refresh(tp);
	if (sk->sk_state == TCP_FIN_WAIT2 && sock_flag(sk, SOCK_DEAD)) {
		if (tp->linger2 >= 0) {
			const int tmo = tcp_fin_time(sk) - TCP_TIMEWAIT_LEN;

			if (tmo > 0) {
				tcp_time_wait(sk, TCP_FIN_WAIT2, tmo);
				goto out;
			}
		}
		tcp_send_active_reset(sk, GFP_ATOMIC);
		goto death;
	}

	if (!sock_flag(sk, SOCK_KEEPOPEN) ||
	    ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_SYN_SENT)))
		goto out;

	elapsed = keepalive_time_when(tp);

	/* It is alive without keepalive 8) */
	if (tp->packets_out || !tcp_write_queue_empty(sk))
		goto resched;

	elapsed = keepalive_time_elapsed(tp);

	if (elapsed >= keepalive_time_when(tp)) {
		/* If the TCP_USER_TIMEOUT option is enabled, use that
		 * to determine when to timeout instead.
		 */
		if ((icsk->icsk_user_timeout != 0 &&
		    elapsed >= msecs_to_jiffies(icsk->icsk_user_timeout) &&
		    icsk->icsk_probes_out > 0) ||
		    (icsk->icsk_user_timeout == 0 &&
		    icsk->icsk_probes_out >= keepalive_probes(tp))) {
			tcp_send_active_reset(sk, GFP_ATOMIC);
			tcp_write_err(sk);
			goto out;
		}
		if (tcp_write_wakeup(sk, LINUX_MIB_TCPKEEPALIVE) <= 0) {
			icsk->icsk_probes_out++;
			elapsed = keepalive_intvl_when(tp);
		} else {
			/* If keepalive was lost due to local congestion,
			 * try harder.
			 */
			elapsed = TCP_RESOURCE_PROBE_INTERVAL;
		}
	} else {
		/* It is tp->rcv_tstamp + keepalive_time_when(tp) */
		elapsed = keepalive_time_when(tp) - elapsed;
	}

	sk_mem_reclaim(sk);

resched:
	inet_csk_reset_keepalive_timer (sk, elapsed);
	goto out;

death:
	tcp_done(sk);

out:
	bh_unlock_sock(sk);
	sock_put(sk);
}