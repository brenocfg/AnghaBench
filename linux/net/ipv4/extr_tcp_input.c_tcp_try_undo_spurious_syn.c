#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ rcv_tsecr; scalar_t__ saw_tstamp; } ;
struct tcp_sock {scalar_t__ retrans_stamp; scalar_t__ undo_marker; TYPE_1__ rx_opt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_try_undo_spurious_syn(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 syn_stamp;

	/* undo_marker is set when SYN or SYNACK times out. The timeout is
	 * spurious if the ACK's timestamp option echo value matches the
	 * original SYN timestamp.
	 */
	syn_stamp = tp->retrans_stamp;
	if (tp->undo_marker && syn_stamp && tp->rx_opt.saw_tstamp &&
	    syn_stamp == tp->rx_opt.rcv_tsecr)
		tp->undo_marker = 0;
}