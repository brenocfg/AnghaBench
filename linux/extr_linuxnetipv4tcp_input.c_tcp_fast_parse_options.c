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
struct tcphdr {int doff; } ;
struct TYPE_2__ {scalar_t__ rcv_tsecr; scalar_t__ saw_tstamp; scalar_t__ tstamp_ok; } ;
struct tcp_sock {scalar_t__ tsoffset; TYPE_1__ rx_opt; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int TCPOLEN_TSTAMP_ALIGNED ; 
 scalar_t__ tcp_parse_aligned_timestamp (struct tcp_sock*,struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_parse_options (struct net const*,struct sk_buff const*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tcp_fast_parse_options(const struct net *net,
				   const struct sk_buff *skb,
				   const struct tcphdr *th, struct tcp_sock *tp)
{
	/* In the spirit of fast parsing, compare doff directly to constant
	 * values.  Because equality is used, short doff can be ignored here.
	 */
	if (th->doff == (sizeof(*th) / 4)) {
		tp->rx_opt.saw_tstamp = 0;
		return false;
	} else if (tp->rx_opt.tstamp_ok &&
		   th->doff == ((sizeof(*th) + TCPOLEN_TSTAMP_ALIGNED) / 4)) {
		if (tcp_parse_aligned_timestamp(tp, th))
			return true;
	}

	tcp_parse_options(net, skb, &tp->rx_opt, 1, NULL);
	if (tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr)
		tp->rx_opt.rcv_tsecr -= tp->tsoffset;

	return true;
}