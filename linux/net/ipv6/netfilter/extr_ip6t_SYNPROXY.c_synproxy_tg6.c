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
struct xt_synproxy_info {int options; int /*<<< orphan*/  mss; } ;
struct xt_action_param {int /*<<< orphan*/  thoff; struct xt_synproxy_info* targinfo; } ;
struct tcphdr {int /*<<< orphan*/  seq; scalar_t__ syn; scalar_t__ rst; scalar_t__ fin; scalar_t__ ack; scalar_t__ cwr; scalar_t__ ece; } ;
struct synproxy_options {int options; int /*<<< orphan*/  mss_option; int /*<<< orphan*/  mss_encode; } ;
struct synproxy_net {TYPE_1__* stats; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  _th ;
struct TYPE_2__ {int /*<<< orphan*/  syn_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 unsigned int NF_DROP ; 
 unsigned int NF_STOLEN ; 
 unsigned int XT_CONTINUE ; 
 int XT_SYNPROXY_OPT_ECN ; 
 int XT_SYNPROXY_OPT_SACK_PERM ; 
 int XT_SYNPROXY_OPT_TIMESTAMP ; 
 int XT_SYNPROXY_OPT_WSCALE ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ nf_ip6_checksum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 
 int /*<<< orphan*/  synproxy_init_timestamp_cookie (struct xt_synproxy_info const*,struct synproxy_options*) ; 
 int /*<<< orphan*/  synproxy_parse_options (struct sk_buff*,int /*<<< orphan*/ ,struct tcphdr*,struct synproxy_options*) ; 
 struct synproxy_net* synproxy_pernet (struct net*) ; 
 scalar_t__ synproxy_recv_client_ack_ipv6 (struct net*,struct sk_buff*,struct tcphdr*,struct synproxy_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synproxy_send_client_synack_ipv6 (struct net*,struct sk_buff*,struct tcphdr*,struct synproxy_options*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_hooknum (struct xt_action_param const*) ; 
 struct net* xt_net (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
synproxy_tg6(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_synproxy_info *info = par->targinfo;
	struct net *net = xt_net(par);
	struct synproxy_net *snet = synproxy_pernet(net);
	struct synproxy_options opts = {};
	struct tcphdr *th, _th;

	if (nf_ip6_checksum(skb, xt_hooknum(par), par->thoff, IPPROTO_TCP))
		return NF_DROP;

	th = skb_header_pointer(skb, par->thoff, sizeof(_th), &_th);
	if (th == NULL)
		return NF_DROP;

	if (!synproxy_parse_options(skb, par->thoff, th, &opts))
		return NF_DROP;

	if (th->syn && !(th->ack || th->fin || th->rst)) {
		/* Initial SYN from client */
		this_cpu_inc(snet->stats->syn_received);

		if (th->ece && th->cwr)
			opts.options |= XT_SYNPROXY_OPT_ECN;

		opts.options &= info->options;
		opts.mss_encode = opts.mss_option;
		opts.mss_option = info->mss;
		if (opts.options & XT_SYNPROXY_OPT_TIMESTAMP)
			synproxy_init_timestamp_cookie(info, &opts);
		else
			opts.options &= ~(XT_SYNPROXY_OPT_WSCALE |
					  XT_SYNPROXY_OPT_SACK_PERM |
					  XT_SYNPROXY_OPT_ECN);

		synproxy_send_client_synack_ipv6(net, skb, th, &opts);
		consume_skb(skb);
		return NF_STOLEN;

	} else if (th->ack && !(th->fin || th->rst || th->syn)) {
		/* ACK from client */
		if (synproxy_recv_client_ack_ipv6(net, skb, th, &opts,
						  ntohl(th->seq))) {
			consume_skb(skb);
			return NF_STOLEN;
		} else {
			return NF_DROP;
		}
	}

	return XT_CONTINUE;
}