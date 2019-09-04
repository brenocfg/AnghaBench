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
typedef  int u64 ;
typedef  int u32 ;
struct vegas {int cntRTT; int minRTT; int baseRTT; int /*<<< orphan*/  beg_snd_nxt; int /*<<< orphan*/  doing_vegas_now; } ;
struct tcp_sock {int snd_cwnd; int snd_cwnd_clamp; void* snd_ssthresh; int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ after (int,int /*<<< orphan*/ ) ; 
 int alpha ; 
 int beta ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int gamma ; 
 struct vegas* inet_csk_ca (struct sock*) ; 
 int min (int,int) ; 
 void* tcp_current_ssthresh (struct sock*) ; 
 scalar_t__ tcp_in_slow_start (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_reno_cong_avoid (struct sock*,int,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start (struct tcp_sock*,int) ; 
 void* tcp_vegas_ssthresh (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_vegas_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct vegas *vegas = inet_csk_ca(sk);

	if (!vegas->doing_vegas_now) {
		tcp_reno_cong_avoid(sk, ack, acked);
		return;
	}

	if (after(ack, vegas->beg_snd_nxt)) {
		/* Do the Vegas once-per-RTT cwnd adjustment. */

		/* Save the extent of the current window so we can use this
		 * at the end of the next RTT.
		 */
		vegas->beg_snd_nxt  = tp->snd_nxt;

		/* We do the Vegas calculations only if we got enough RTT
		 * samples that we can be reasonably sure that we got
		 * at least one RTT sample that wasn't from a delayed ACK.
		 * If we only had 2 samples total,
		 * then that means we're getting only 1 ACK per RTT, which
		 * means they're almost certainly delayed ACKs.
		 * If  we have 3 samples, we should be OK.
		 */

		if (vegas->cntRTT <= 2) {
			/* We don't have enough RTT samples to do the Vegas
			 * calculation, so we'll behave like Reno.
			 */
			tcp_reno_cong_avoid(sk, ack, acked);
		} else {
			u32 rtt, diff;
			u64 target_cwnd;

			/* We have enough RTT samples, so, using the Vegas
			 * algorithm, we determine if we should increase or
			 * decrease cwnd, and by how much.
			 */

			/* Pluck out the RTT we are using for the Vegas
			 * calculations. This is the min RTT seen during the
			 * last RTT. Taking the min filters out the effects
			 * of delayed ACKs, at the cost of noticing congestion
			 * a bit later.
			 */
			rtt = vegas->minRTT;

			/* Calculate the cwnd we should have, if we weren't
			 * going too fast.
			 *
			 * This is:
			 *     (actual rate in segments) * baseRTT
			 */
			target_cwnd = (u64)tp->snd_cwnd * vegas->baseRTT;
			do_div(target_cwnd, rtt);

			/* Calculate the difference between the window we had,
			 * and the window we would like to have. This quantity
			 * is the "Diff" from the Arizona Vegas papers.
			 */
			diff = tp->snd_cwnd * (rtt-vegas->baseRTT) / vegas->baseRTT;

			if (diff > gamma && tcp_in_slow_start(tp)) {
				/* Going too fast. Time to slow down
				 * and switch to congestion avoidance.
				 */

				/* Set cwnd to match the actual rate
				 * exactly:
				 *   cwnd = (actual rate) * baseRTT
				 * Then we add 1 because the integer
				 * truncation robs us of full link
				 * utilization.
				 */
				tp->snd_cwnd = min(tp->snd_cwnd, (u32)target_cwnd+1);
				tp->snd_ssthresh = tcp_vegas_ssthresh(tp);

			} else if (tcp_in_slow_start(tp)) {
				/* Slow start.  */
				tcp_slow_start(tp, acked);
			} else {
				/* Congestion avoidance. */

				/* Figure out where we would like cwnd
				 * to be.
				 */
				if (diff > beta) {
					/* The old window was too fast, so
					 * we slow down.
					 */
					tp->snd_cwnd--;
					tp->snd_ssthresh
						= tcp_vegas_ssthresh(tp);
				} else if (diff < alpha) {
					/* We don't have enough extra packets
					 * in the network, so speed up.
					 */
					tp->snd_cwnd++;
				} else {
					/* Sending just as fast as we
					 * should be.
					 */
				}
			}

			if (tp->snd_cwnd < 2)
				tp->snd_cwnd = 2;
			else if (tp->snd_cwnd > tp->snd_cwnd_clamp)
				tp->snd_cwnd = tp->snd_cwnd_clamp;

			tp->snd_ssthresh = tcp_current_ssthresh(sk);
		}

		/* Wipe the slate clean for the next RTT. */
		vegas->cntRTT = 0;
		vegas->minRTT = 0x7fffffff;
	}
	/* Use normal slow start */
	else if (tcp_in_slow_start(tp))
		tcp_slow_start(tp, acked);
}