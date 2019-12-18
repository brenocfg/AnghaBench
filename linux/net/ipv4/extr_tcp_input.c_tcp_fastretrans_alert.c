#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  probe_seq_start; } ;
struct tcp_sock {scalar_t__ retrans_out; int /*<<< orphan*/  snd_cwnd; TYPE_2__ mtu_probe; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  high_seq; scalar_t__ retrans_stamp; scalar_t__ prior_ssthresh; scalar_t__ sacked_out; int /*<<< orphan*/  packets_out; } ;
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  probe_size; } ;
struct inet_connection_sock {int icsk_ca_state; TYPE_1__ icsk_mtup; } ;

/* Variables and functions */
 int FLAG_DATA_SACKED ; 
 int FLAG_ECE ; 
 int FLAG_LOST_RETRANS ; 
 int FLAG_SND_UNA_ADVANCED ; 
 int REXMIT_LOST ; 
#define  TCP_CA_CWR 130 
 int TCP_CA_Disorder ; 
#define  TCP_CA_Loss 129 
 int TCP_CA_Open ; 
#define  TCP_CA_Recovery 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_add_reno_sack (struct sock*,int) ; 
 scalar_t__ tcp_check_sack_reneging (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_end_cwnd_reduction (struct sock*) ; 
 int /*<<< orphan*/  tcp_enter_recovery (struct sock*,int) ; 
 scalar_t__ tcp_force_fast_retransmit (struct sock*) ; 
 int /*<<< orphan*/  tcp_identify_packet_loss (struct sock*,int*) ; 
 int /*<<< orphan*/  tcp_is_rack (struct sock*) ; 
 int /*<<< orphan*/  tcp_is_reno (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mtup_probe_failed (struct sock*) ; 
 int /*<<< orphan*/  tcp_process_loss (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  tcp_reset_reno_sack (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_simple_retransmit (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_to_recover (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_try_keep_open (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_to_open (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_try_undo_dsack (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_undo_partial (struct sock*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tcp_try_undo_recovery (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_scoreboard (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_fastretrans_alert(struct sock *sk, const u32 prior_snd_una,
				  int num_dupack, int *ack_flag, int *rexmit)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int fast_rexmit = 0, flag = *ack_flag;
	bool do_lost = num_dupack || ((flag & FLAG_DATA_SACKED) &&
				      tcp_force_fast_retransmit(sk));

	if (!tp->packets_out && tp->sacked_out)
		tp->sacked_out = 0;

	/* Now state machine starts.
	 * A. ECE, hence prohibit cwnd undoing, the reduction is required. */
	if (flag & FLAG_ECE)
		tp->prior_ssthresh = 0;

	/* B. In all the states check for reneging SACKs. */
	if (tcp_check_sack_reneging(sk, flag))
		return;

	/* C. Check consistency of the current state. */
	tcp_verify_left_out(tp);

	/* D. Check state exit conditions. State can be terminated
	 *    when high_seq is ACKed. */
	if (icsk->icsk_ca_state == TCP_CA_Open) {
		WARN_ON(tp->retrans_out != 0);
		tp->retrans_stamp = 0;
	} else if (!before(tp->snd_una, tp->high_seq)) {
		switch (icsk->icsk_ca_state) {
		case TCP_CA_CWR:
			/* CWR is to be held something *above* high_seq
			 * is ACKed for CWR bit to reach receiver. */
			if (tp->snd_una != tp->high_seq) {
				tcp_end_cwnd_reduction(sk);
				tcp_set_ca_state(sk, TCP_CA_Open);
			}
			break;

		case TCP_CA_Recovery:
			if (tcp_is_reno(tp))
				tcp_reset_reno_sack(tp);
			if (tcp_try_undo_recovery(sk))
				return;
			tcp_end_cwnd_reduction(sk);
			break;
		}
	}

	/* E. Process state. */
	switch (icsk->icsk_ca_state) {
	case TCP_CA_Recovery:
		if (!(flag & FLAG_SND_UNA_ADVANCED)) {
			if (tcp_is_reno(tp))
				tcp_add_reno_sack(sk, num_dupack);
		} else {
			if (tcp_try_undo_partial(sk, prior_snd_una))
				return;
			/* Partial ACK arrived. Force fast retransmit. */
			do_lost = tcp_is_reno(tp) ||
				  tcp_force_fast_retransmit(sk);
		}
		if (tcp_try_undo_dsack(sk)) {
			tcp_try_keep_open(sk);
			return;
		}
		tcp_identify_packet_loss(sk, ack_flag);
		break;
	case TCP_CA_Loss:
		tcp_process_loss(sk, flag, num_dupack, rexmit);
		tcp_identify_packet_loss(sk, ack_flag);
		if (!(icsk->icsk_ca_state == TCP_CA_Open ||
		      (*ack_flag & FLAG_LOST_RETRANS)))
			return;
		/* Change state if cwnd is undone or retransmits are lost */
		/* fall through */
	default:
		if (tcp_is_reno(tp)) {
			if (flag & FLAG_SND_UNA_ADVANCED)
				tcp_reset_reno_sack(tp);
			tcp_add_reno_sack(sk, num_dupack);
		}

		if (icsk->icsk_ca_state <= TCP_CA_Disorder)
			tcp_try_undo_dsack(sk);

		tcp_identify_packet_loss(sk, ack_flag);
		if (!tcp_time_to_recover(sk, flag)) {
			tcp_try_to_open(sk, flag);
			return;
		}

		/* MTU probe failure: don't reduce cwnd */
		if (icsk->icsk_ca_state < TCP_CA_CWR &&
		    icsk->icsk_mtup.probe_size &&
		    tp->snd_una == tp->mtu_probe.probe_seq_start) {
			tcp_mtup_probe_failed(sk);
			/* Restores the reduction we did in tcp_mtup_probe() */
			tp->snd_cwnd++;
			tcp_simple_retransmit(sk);
			return;
		}

		/* Otherwise enter Recovery state */
		tcp_enter_recovery(sk, (flag & FLAG_ECE));
		fast_rexmit = 1;
	}

	if (!tcp_is_rack(sk) && do_lost)
		tcp_update_scoreboard(sk, fast_rexmit);
	*rexmit = REXMIT_LOST;
}