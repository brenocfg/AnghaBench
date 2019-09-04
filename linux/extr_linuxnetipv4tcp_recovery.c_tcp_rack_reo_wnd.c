#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int reo_wnd_steps; } ;
struct tcp_sock {scalar_t__ sacked_out; scalar_t__ reordering; int srtt_us; TYPE_1__ rack; int /*<<< orphan*/  reord_seen; } ;
struct sock {int dummy; } ;
struct TYPE_8__ {scalar_t__ icsk_ca_state; } ;
struct TYPE_6__ {int sysctl_tcp_recovery; } ;
struct TYPE_7__ {TYPE_2__ ipv4; } ;

/* Variables and functions */
 scalar_t__ TCP_CA_Recovery ; 
 int TCP_RACK_NO_DUPTHRESH ; 
 TYPE_4__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 TYPE_3__* sock_net (struct sock const*) ; 
 int tcp_min_rtt (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 

__attribute__((used)) static u32 tcp_rack_reo_wnd(const struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (!tp->reord_seen) {
		/* If reordering has not been observed, be aggressive during
		 * the recovery or starting the recovery by DUPACK threshold.
		 */
		if (inet_csk(sk)->icsk_ca_state >= TCP_CA_Recovery)
			return 0;

		if (tp->sacked_out >= tp->reordering &&
		    !(sock_net(sk)->ipv4.sysctl_tcp_recovery & TCP_RACK_NO_DUPTHRESH))
			return 0;
	}

	/* To be more reordering resilient, allow min_rtt/4 settling delay.
	 * Use min_rtt instead of the smoothed RTT because reordering is
	 * often a path property and less related to queuing or delayed ACKs.
	 * Upon receiving DSACKs, linearly increase the window up to the
	 * smoothed RTT.
	 */
	return min((tcp_min_rtt(tp) >> 2) * tp->rack.reo_wnd_steps,
		   tp->srtt_us >> 3);
}