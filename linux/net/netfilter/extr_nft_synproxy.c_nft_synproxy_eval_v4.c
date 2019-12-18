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
struct tcphdr {int /*<<< orphan*/  seq; scalar_t__ ack; scalar_t__ syn; } ;
struct synproxy_options {int dummy; } ;
struct synproxy_net {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nf_synproxy_info {int dummy; } ;
struct nft_synproxy {struct nf_synproxy_info info; } ;
struct TYPE_2__ {void* code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct net {int dummy; } ;

/* Variables and functions */
 void* NF_DROP ; 
 void* NF_STOLEN ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct net* nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_synproxy_tcp_options (struct synproxy_options*,struct tcphdr const*,struct synproxy_net*,struct nf_synproxy_info*,struct nft_synproxy const*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct synproxy_net* synproxy_pernet (struct net*) ; 
 scalar_t__ synproxy_recv_client_ack (struct net*,struct sk_buff*,struct tcphdr const*,struct synproxy_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synproxy_send_client_synack (struct net*,struct sk_buff*,struct tcphdr const*,struct synproxy_options*) ; 

__attribute__((used)) static void nft_synproxy_eval_v4(const struct nft_synproxy *priv,
				 struct nft_regs *regs,
				 const struct nft_pktinfo *pkt,
				 const struct tcphdr *tcp,
				 struct tcphdr *_tcph,
				 struct synproxy_options *opts)
{
	struct nf_synproxy_info info = priv->info;
	struct net *net = nft_net(pkt);
	struct synproxy_net *snet = synproxy_pernet(net);
	struct sk_buff *skb = pkt->skb;

	if (tcp->syn) {
		/* Initial SYN from client */
		nft_synproxy_tcp_options(opts, tcp, snet, &info, priv);
		synproxy_send_client_synack(net, skb, tcp, opts);
		consume_skb(skb);
		regs->verdict.code = NF_STOLEN;
	} else if (tcp->ack) {
		/* ACK from client */
		if (synproxy_recv_client_ack(net, skb, tcp, opts,
					     ntohl(tcp->seq))) {
			consume_skb(skb);
			regs->verdict.code = NF_STOLEN;
		} else {
			regs->verdict.code = NF_DROP;
		}
	}
}