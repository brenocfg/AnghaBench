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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {scalar_t__ tlp_high_seq; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int FLAG_DATA_SACKED ; 
 int FLAG_DSACKING_ACK ; 
 int FLAG_NOT_DUP ; 
 int FLAG_SND_UNA_ADVANCED ; 
 int /*<<< orphan*/  LINUX_MIB_TCPLOSSPROBERECOVERY ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_CA_CWR ; 
 scalar_t__ after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_end_cwnd_reduction (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_cwnd_reduction (struct sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_keep_open (struct sock*) ; 

__attribute__((used)) static void tcp_process_tlp_ack(struct sock *sk, u32 ack, int flag)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (before(ack, tp->tlp_high_seq))
		return;

	if (flag & FLAG_DSACKING_ACK) {
		/* This DSACK means original and TLP probe arrived; no loss */
		tp->tlp_high_seq = 0;
	} else if (after(ack, tp->tlp_high_seq)) {
		/* ACK advances: there was a loss, so reduce cwnd. Reset
		 * tlp_high_seq in tcp_init_cwnd_reduction()
		 */
		tcp_init_cwnd_reduction(sk);
		tcp_set_ca_state(sk, TCP_CA_CWR);
		tcp_end_cwnd_reduction(sk);
		tcp_try_keep_open(sk);
		NET_INC_STATS(sock_net(sk),
				LINUX_MIB_TCPLOSSPROBERECOVERY);
	} else if (!(flag & (FLAG_SND_UNA_ADVANCED |
			     FLAG_NOT_DUP | FLAG_DATA_SACKED))) {
		/* Pure dupack: original and TLP probe arrived; no loss */
		tp->tlp_high_seq = 0;
	}
}