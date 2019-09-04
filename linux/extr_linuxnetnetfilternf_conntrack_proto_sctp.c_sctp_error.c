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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {unsigned int len; scalar_t__ ip_summed; scalar_t__ data; } ;
struct sctphdr {scalar_t__ checksum; } ;
struct nf_conn {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 int /*<<< orphan*/  nf_l4proto_log_invalid (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ sctp_compute_cksum (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int sctp_error(struct net *net, struct nf_conn *tpl, struct sk_buff *skb,
		      unsigned int dataoff,
		      u8 pf, unsigned int hooknum)
{
	const struct sctphdr *sh;
	const char *logmsg;

	if (skb->len < dataoff + sizeof(struct sctphdr)) {
		logmsg = "nf_ct_sctp: short packet ";
		goto out_invalid;
	}
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    skb->ip_summed == CHECKSUM_NONE) {
		if (!skb_make_writable(skb, dataoff + sizeof(struct sctphdr))) {
			logmsg = "nf_ct_sctp: failed to read header ";
			goto out_invalid;
		}
		sh = (const struct sctphdr *)(skb->data + dataoff);
		if (sh->checksum != sctp_compute_cksum(skb, dataoff)) {
			logmsg = "nf_ct_sctp: bad CRC ";
			goto out_invalid;
		}
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
	return NF_ACCEPT;
out_invalid:
	nf_l4proto_log_invalid(skb, net, pf, IPPROTO_SCTP, "%s", logmsg);
	return -NF_ACCEPT;
}