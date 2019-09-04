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
struct tcp_sock {scalar_t__ retrans_stamp; scalar_t__ retrans_out; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPPARTIALUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_any_retrans_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_check_sack_reordering (struct sock*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcp_packet_delayed (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_keep_open (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwnd_reduction (struct sock*,int) ; 

__attribute__((used)) static bool tcp_try_undo_partial(struct sock *sk, u32 prior_snd_una)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->undo_marker && tcp_packet_delayed(tp)) {
		/* Plain luck! Hole if filled with delayed
		 * packet, rather than with a retransmit. Check reordering.
		 */
		tcp_check_sack_reordering(sk, prior_snd_una, 1);

		/* We are getting evidence that the reordering degree is higher
		 * than we realized. If there are no retransmits out then we
		 * can undo. Otherwise we clock out new packets but do not
		 * mark more packets lost or retransmit more.
		 */
		if (tp->retrans_out)
			return true;

		if (!tcp_any_retrans_done(sk))
			tp->retrans_stamp = 0;

		DBGUNDO(sk, "partial recovery");
		tcp_undo_cwnd_reduction(sk, true);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPPARTIALUNDO);
		tcp_try_keep_open(sk);
		return true;
	}
	return false;
}