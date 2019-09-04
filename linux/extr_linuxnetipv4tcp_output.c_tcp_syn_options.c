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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  rcv_wscale; int /*<<< orphan*/  ts_recent; } ;
struct tcp_sock {int syn_fastopen; int syn_fastopen_exp; TYPE_1__ rx_opt; scalar_t__ tsoffset; struct tcp_fastopen_request* fastopen_req; } ;
struct tcp_out_options {int options; TYPE_3__* fastopen_cookie; int /*<<< orphan*/  ws; int /*<<< orphan*/  tsecr; scalar_t__ tsval; int /*<<< orphan*/  mss; } ;
struct tcp_md5sig_key {int dummy; } ;
struct TYPE_7__ {scalar_t__ len; scalar_t__ exp; } ;
struct tcp_fastopen_request {TYPE_3__ cookie; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int sysctl_tcp_window_scaling; int sysctl_tcp_sack; scalar_t__ sysctl_tcp_timestamps; } ;
struct TYPE_8__ {TYPE_2__ ipv4; } ;

/* Variables and functions */
 unsigned int MAX_TCP_OPTION_SPACE ; 
 int OPTION_FAST_OPEN_COOKIE ; 
 int OPTION_SACK_ADVERTISE ; 
 int OPTION_TS ; 
 int OPTION_WSCALE ; 
 scalar_t__ TCPOLEN_EXP_FASTOPEN_BASE ; 
 scalar_t__ TCPOLEN_FASTOPEN_BASE ; 
 scalar_t__ TCPOLEN_MSS_ALIGNED ; 
 scalar_t__ TCPOLEN_SACKPERM_ALIGNED ; 
 scalar_t__ TCPOLEN_TSTAMP_ALIGNED ; 
 scalar_t__ TCPOLEN_WSCALE_ALIGNED ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smc_set_option (struct tcp_sock*,struct tcp_out_options*,unsigned int*) ; 
 TYPE_4__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_advertise_mss (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_skb_timestamp (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int tcp_syn_options(struct sock *sk, struct sk_buff *skb,
				struct tcp_out_options *opts,
				struct tcp_md5sig_key **md5)
{
	struct tcp_sock *tp = tcp_sk(sk);
	unsigned int remaining = MAX_TCP_OPTION_SPACE;
	struct tcp_fastopen_request *fastopen = tp->fastopen_req;

	*md5 = NULL;
#ifdef CONFIG_TCP_MD5SIG
	if (unlikely(rcu_access_pointer(tp->md5sig_info))) {
		*md5 = tp->af_specific->md5_lookup(sk, sk);
		if (*md5) {
			opts->options |= OPTION_MD5;
			remaining -= TCPOLEN_MD5SIG_ALIGNED;
		}
	}
#endif

	/* We always get an MSS option.  The option bytes which will be seen in
	 * normal data packets should timestamps be used, must be in the MSS
	 * advertised.  But we subtract them from tp->mss_cache so that
	 * calculations in tcp_sendmsg are simpler etc.  So account for this
	 * fact here if necessary.  If we don't do this correctly, as a
	 * receiver we won't recognize data packets as being full sized when we
	 * should, and thus we won't abide by the delayed ACK rules correctly.
	 * SACKs don't matter, we never delay an ACK when we have any of those
	 * going out.  */
	opts->mss = tcp_advertise_mss(sk);
	remaining -= TCPOLEN_MSS_ALIGNED;

	if (likely(sock_net(sk)->ipv4.sysctl_tcp_timestamps && !*md5)) {
		opts->options |= OPTION_TS;
		opts->tsval = tcp_skb_timestamp(skb) + tp->tsoffset;
		opts->tsecr = tp->rx_opt.ts_recent;
		remaining -= TCPOLEN_TSTAMP_ALIGNED;
	}
	if (likely(sock_net(sk)->ipv4.sysctl_tcp_window_scaling)) {
		opts->ws = tp->rx_opt.rcv_wscale;
		opts->options |= OPTION_WSCALE;
		remaining -= TCPOLEN_WSCALE_ALIGNED;
	}
	if (likely(sock_net(sk)->ipv4.sysctl_tcp_sack)) {
		opts->options |= OPTION_SACK_ADVERTISE;
		if (unlikely(!(OPTION_TS & opts->options)))
			remaining -= TCPOLEN_SACKPERM_ALIGNED;
	}

	if (fastopen && fastopen->cookie.len >= 0) {
		u32 need = fastopen->cookie.len;

		need += fastopen->cookie.exp ? TCPOLEN_EXP_FASTOPEN_BASE :
					       TCPOLEN_FASTOPEN_BASE;
		need = (need + 3) & ~3U;  /* Align to 32 bits */
		if (remaining >= need) {
			opts->options |= OPTION_FAST_OPEN_COOKIE;
			opts->fastopen_cookie = &fastopen->cookie;
			remaining -= need;
			tp->syn_fastopen = 1;
			tp->syn_fastopen_exp = fastopen->cookie.exp ? 1 : 0;
		}
	}

	smc_set_option(tp, opts, &remaining);

	return MAX_TCP_OPTION_SPACE - remaining;
}