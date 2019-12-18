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
typedef  int u32 ;
struct tcp_options_received {int rcv_tsecr; int wscale_ok; int snd_wscale; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  saw_tstamp; } ;
struct TYPE_2__ {scalar_t__ sysctl_tcp_window_scaling; int /*<<< orphan*/  sysctl_tcp_sack; int /*<<< orphan*/  sysctl_tcp_timestamps; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_SACK_SEEN ; 
 int TS_OPT_SACK ; 
 int TS_OPT_WSCALE_MASK ; 
 int /*<<< orphan*/  tcp_clear_options (struct tcp_options_received*) ; 

bool cookie_timestamp_decode(const struct net *net,
			     struct tcp_options_received *tcp_opt)
{
	/* echoed timestamp, lowest bits contain options */
	u32 options = tcp_opt->rcv_tsecr;

	if (!tcp_opt->saw_tstamp)  {
		tcp_clear_options(tcp_opt);
		return true;
	}

	if (!net->ipv4.sysctl_tcp_timestamps)
		return false;

	tcp_opt->sack_ok = (options & TS_OPT_SACK) ? TCP_SACK_SEEN : 0;

	if (tcp_opt->sack_ok && !net->ipv4.sysctl_tcp_sack)
		return false;

	if ((options & TS_OPT_WSCALE_MASK) == TS_OPT_WSCALE_MASK)
		return true; /* no window scaling */

	tcp_opt->wscale_ok = 1;
	tcp_opt->snd_wscale = options & TS_OPT_WSCALE_MASK;

	return net->ipv4.sysctl_tcp_window_scaling != 0;
}