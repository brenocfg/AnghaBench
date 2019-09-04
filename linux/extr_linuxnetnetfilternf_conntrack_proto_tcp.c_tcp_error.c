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
typedef  size_t u_int8_t ;
struct tcphdr {int doff; } ;
struct sk_buff {unsigned int len; } ;
struct nf_conn {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 size_t TCPHDR_CWR ; 
 size_t TCPHDR_ECE ; 
 size_t TCPHDR_PSH ; 
 scalar_t__ nf_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ,size_t) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_error_log (struct sk_buff*,struct net*,size_t,char*) ; 
 size_t tcp_flag_byte (struct tcphdr const*) ; 
 int /*<<< orphan*/ * tcp_valid_flags ; 

__attribute__((used)) static int tcp_error(struct net *net, struct nf_conn *tmpl,
		     struct sk_buff *skb,
		     unsigned int dataoff,
		     u_int8_t pf,
		     unsigned int hooknum)
{
	const struct tcphdr *th;
	struct tcphdr _tcph;
	unsigned int tcplen = skb->len - dataoff;
	u_int8_t tcpflags;

	/* Smaller that minimal TCP header? */
	th = skb_header_pointer(skb, dataoff, sizeof(_tcph), &_tcph);
	if (th == NULL) {
		tcp_error_log(skb, net, pf, "short packet");
		return -NF_ACCEPT;
	}

	/* Not whole TCP header or malformed packet */
	if (th->doff*4 < sizeof(struct tcphdr) || tcplen < th->doff*4) {
		tcp_error_log(skb, net, pf, "truncated packet");
		return -NF_ACCEPT;
	}

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 */
	/* FIXME: Source route IP option packets --RR */
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    nf_checksum(skb, hooknum, dataoff, IPPROTO_TCP, pf)) {
		tcp_error_log(skb, net, pf, "bad checksum");
		return -NF_ACCEPT;
	}

	/* Check TCP flags. */
	tcpflags = (tcp_flag_byte(th) & ~(TCPHDR_ECE|TCPHDR_CWR|TCPHDR_PSH));
	if (!tcp_valid_flags[tcpflags]) {
		tcp_error_log(skb, net, pf, "invalid tcp flag combination");
		return -NF_ACCEPT;
	}

	return NF_ACCEPT;
}