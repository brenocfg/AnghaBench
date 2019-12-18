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
struct tcp_sock {int /*<<< orphan*/  high_seq; int /*<<< orphan*/  snd_nxt; scalar_t__ frto; int /*<<< orphan*/  fastopen_rsk; int /*<<< orphan*/  snd_una; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int FLAG_DATA_SACKED ; 
 int FLAG_ORIG_SACK_ACKED ; 
 int FLAG_SND_UNA_ADVANCED ; 
 int REXMIT_LOST ; 
 int REXMIT_NEW ; 
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_add_reno_sack (struct sock*,int) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_reset_reno_sack (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_try_undo_loss (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_try_undo_recovery (struct sock*) ; 
 int /*<<< orphan*/  tcp_wnd_end (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_empty (struct sock*) ; 

__attribute__((used)) static void tcp_process_loss(struct sock *sk, int flag, int num_dupack,
			     int *rexmit)
{
	struct tcp_sock *tp = tcp_sk(sk);
	bool recovered = !before(tp->snd_una, tp->high_seq);

	if ((flag & FLAG_SND_UNA_ADVANCED || rcu_access_pointer(tp->fastopen_rsk)) &&
	    tcp_try_undo_loss(sk, false))
		return;

	if (tp->frto) { /* F-RTO RFC5682 sec 3.1 (sack enhanced version). */
		/* Step 3.b. A timeout is spurious if not all data are
		 * lost, i.e., never-retransmitted data are (s)acked.
		 */
		if ((flag & FLAG_ORIG_SACK_ACKED) &&
		    tcp_try_undo_loss(sk, true))
			return;

		if (after(tp->snd_nxt, tp->high_seq)) {
			if (flag & FLAG_DATA_SACKED || num_dupack)
				tp->frto = 0; /* Step 3.a. loss was real */
		} else if (flag & FLAG_SND_UNA_ADVANCED && !recovered) {
			tp->high_seq = tp->snd_nxt;
			/* Step 2.b. Try send new data (but deferred until cwnd
			 * is updated in tcp_ack()). Otherwise fall back to
			 * the conventional recovery.
			 */
			if (!tcp_write_queue_empty(sk) &&
			    after(tcp_wnd_end(tp), tp->snd_nxt)) {
				*rexmit = REXMIT_NEW;
				return;
			}
			tp->frto = 0;
		}
	}

	if (recovered) {
		/* F-RTO RFC5682 sec 3.1 step 2.a and 1st part of step 3.a */
		tcp_try_undo_recovery(sk);
		return;
	}
	if (tcp_is_reno(tp)) {
		/* A Reno DUPACK means new data in F-RTO step 2.b above are
		 * delivered. Lower inflight to clock out (re)tranmissions.
		 */
		if (after(tp->snd_nxt, tp->high_seq) && num_dupack)
			tcp_add_reno_sack(sk, num_dupack);
		else if (flag & FLAG_SND_UNA_ADVANCED)
			tcp_reset_reno_sack(tp);
	}
	*rexmit = REXMIT_LOST;
}