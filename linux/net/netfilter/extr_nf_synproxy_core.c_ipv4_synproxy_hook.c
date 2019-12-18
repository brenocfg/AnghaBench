#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int /*<<< orphan*/  seq; int /*<<< orphan*/  ack; int /*<<< orphan*/  syn; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  rst; } ;
struct synproxy_options {int options; scalar_t__ tsecr; scalar_t__ tsval; } ;
struct synproxy_net {TYPE_2__* stats; } ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {struct net* net; } ;
struct nf_conn_synproxy {scalar_t__ isn; scalar_t__ its; scalar_t__ tsoff; } ;
struct ip_ct_tcp {int state; } ;
struct TYPE_4__ {struct ip_ct_tcp tcp; } ;
struct nf_conn {TYPE_1__ proto; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _th ;
struct TYPE_6__ {scalar_t__ protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  cookie_retrans; int /*<<< orphan*/  conn_reopened; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTINFO2DIR (int) ; 
 int /*<<< orphan*/  IPCT_SEQADJ ; 
 int /*<<< orphan*/  IPCT_SYNPROXY ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 unsigned int NF_STOLEN ; 
 int NF_SYNPROXY_OPT_MSS ; 
 int NF_SYNPROXY_OPT_SACK_PERM ; 
 int NF_SYNPROXY_OPT_TIMESTAMP ; 
 int NF_SYNPROXY_OPT_WSCALE ; 
#define  TCP_CONNTRACK_CLOSE 130 
#define  TCP_CONNTRACK_SYN_RECV 129 
#define  TCP_CONNTRACK_SYN_SENT 128 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_seqadj_init (struct nf_conn*,int,scalar_t__) ; 
 scalar_t__ nf_is_loopback_packet (struct sk_buff*) ; 
 struct nf_conn_synproxy* nfct_synproxy (struct nf_conn*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  synproxy_parse_options (struct sk_buff*,unsigned int,struct tcphdr*,struct synproxy_options*) ; 
 struct synproxy_net* synproxy_pernet (struct net*) ; 
 int /*<<< orphan*/  synproxy_recv_client_ack (struct net*,struct sk_buff*,struct tcphdr*,struct synproxy_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synproxy_send_client_ack (struct net*,struct sk_buff*,struct tcphdr*,struct synproxy_options*) ; 
 int /*<<< orphan*/  synproxy_send_server_ack (struct net*,struct ip_ct_tcp const*,struct sk_buff*,struct tcphdr*,struct synproxy_options*) ; 
 int /*<<< orphan*/  synproxy_tstamp_adjust (struct sk_buff*,unsigned int,struct tcphdr*,struct nf_conn*,int,struct nf_conn_synproxy*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

unsigned int
ipv4_synproxy_hook(void *priv, struct sk_buff *skb,
		   const struct nf_hook_state *nhs)
{
	struct net *net = nhs->net;
	struct synproxy_net *snet = synproxy_pernet(net);
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;
	struct nf_conn_synproxy *synproxy;
	struct synproxy_options opts = {};
	const struct ip_ct_tcp *state;
	struct tcphdr *th, _th;
	unsigned int thoff;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		return NF_ACCEPT;

	synproxy = nfct_synproxy(ct);
	if (!synproxy)
		return NF_ACCEPT;

	if (nf_is_loopback_packet(skb) ||
	    ip_hdr(skb)->protocol != IPPROTO_TCP)
		return NF_ACCEPT;

	thoff = ip_hdrlen(skb);
	th = skb_header_pointer(skb, thoff, sizeof(_th), &_th);
	if (!th)
		return NF_DROP;

	state = &ct->proto.tcp;
	switch (state->state) {
	case TCP_CONNTRACK_CLOSE:
		if (th->rst && CTINFO2DIR(ctinfo) != IP_CT_DIR_ORIGINAL) {
			nf_ct_seqadj_init(ct, ctinfo, synproxy->isn -
						      ntohl(th->seq) + 1);
			break;
		}

		if (!th->syn || th->ack ||
		    CTINFO2DIR(ctinfo) != IP_CT_DIR_ORIGINAL)
			break;

		/* Reopened connection - reset the sequence number and timestamp
		 * adjustments, they will get initialized once the connection is
		 * reestablished.
		 */
		nf_ct_seqadj_init(ct, ctinfo, 0);
		synproxy->tsoff = 0;
		this_cpu_inc(snet->stats->conn_reopened);

		/* fall through */
	case TCP_CONNTRACK_SYN_SENT:
		if (!synproxy_parse_options(skb, thoff, th, &opts))
			return NF_DROP;

		if (!th->syn && th->ack &&
		    CTINFO2DIR(ctinfo) == IP_CT_DIR_ORIGINAL) {
			/* Keep-Alives are sent with SEG.SEQ = SND.NXT-1,
			 * therefore we need to add 1 to make the SYN sequence
			 * number match the one of first SYN.
			 */
			if (synproxy_recv_client_ack(net, skb, th, &opts,
						     ntohl(th->seq) + 1)) {
				this_cpu_inc(snet->stats->cookie_retrans);
				consume_skb(skb);
				return NF_STOLEN;
			} else {
				return NF_DROP;
			}
		}

		synproxy->isn = ntohl(th->ack_seq);
		if (opts.options & NF_SYNPROXY_OPT_TIMESTAMP)
			synproxy->its = opts.tsecr;

		nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		break;
	case TCP_CONNTRACK_SYN_RECV:
		if (!th->syn || !th->ack)
			break;

		if (!synproxy_parse_options(skb, thoff, th, &opts))
			return NF_DROP;

		if (opts.options & NF_SYNPROXY_OPT_TIMESTAMP) {
			synproxy->tsoff = opts.tsval - synproxy->its;
			nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		}

		opts.options &= ~(NF_SYNPROXY_OPT_MSS |
				  NF_SYNPROXY_OPT_WSCALE |
				  NF_SYNPROXY_OPT_SACK_PERM);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_server_ack(net, state, skb, th, &opts);

		nf_ct_seqadj_init(ct, ctinfo, synproxy->isn - ntohl(th->seq));
		nf_conntrack_event_cache(IPCT_SEQADJ, ct);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_client_ack(net, skb, th, &opts);

		consume_skb(skb);
		return NF_STOLEN;
	default:
		break;
	}

	synproxy_tstamp_adjust(skb, thoff, th, ct, ctinfo, synproxy);
	return NF_ACCEPT;
}