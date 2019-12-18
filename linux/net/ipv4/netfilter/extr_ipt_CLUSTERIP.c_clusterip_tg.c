#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct xt_action_param {struct ipt_clusterip_tgt_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; } ;
struct nf_conn {int /*<<< orphan*/  mark; TYPE_1__* tuplehash; } ;
struct ipt_clusterip_tgt_info {int /*<<< orphan*/  config; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {scalar_t__ protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 size_t IP_CT_DIR_ORIGINAL ; 
#define  IP_CT_ESTABLISHED 132 
#define  IP_CT_ESTABLISHED_REPLY 131 
#define  IP_CT_NEW 130 
#define  IP_CT_RELATED 129 
#define  IP_CT_RELATED_REPLY 128 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  clusterip_hashfn (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_responsible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple_ip (int /*<<< orphan*/ *) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static unsigned int
clusterip_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ipt_clusterip_tgt_info *cipinfo = par->targinfo;
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	u_int32_t hash;

	/* don't need to clusterip_config_get() here, since refcount
	 * is only decremented by destroy() - and ip_tables guarantees
	 * that the ->target() function isn't called after ->destroy() */

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return NF_DROP;

	/* special case: ICMP error handling. conntrack distinguishes between
	 * error messages (RELATED) and information requests (see below) */
	if (ip_hdr(skb)->protocol == IPPROTO_ICMP &&
	    (ctinfo == IP_CT_RELATED ||
	     ctinfo == IP_CT_RELATED_REPLY))
		return XT_CONTINUE;

	/* nf_conntrack_proto_icmp guarantees us that we only have ICMP_ECHO,
	 * TIMESTAMP, INFO_REQUEST or ICMP_ADDRESS type icmp packets from here
	 * on, which all have an ID field [relevant for hashing]. */

	hash = clusterip_hashfn(skb, cipinfo->config);

	switch (ctinfo) {
	case IP_CT_NEW:
		ct->mark = hash;
		break;
	case IP_CT_RELATED:
	case IP_CT_RELATED_REPLY:
		/* FIXME: we don't handle expectations at the moment.
		 * They can arrive on a different node than
		 * the master connection (e.g. FTP passive mode) */
	case IP_CT_ESTABLISHED:
	case IP_CT_ESTABLISHED_REPLY:
		break;
	default:			/* Prevent gcc warnings */
		break;
	}

#ifdef DEBUG
	nf_ct_dump_tuple_ip(&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
#endif
	pr_debug("hash=%u ct_hash=%u ", hash, ct->mark);
	if (!clusterip_responsible(cipinfo->config, hash)) {
		pr_debug("not responsible\n");
		return NF_DROP;
	}
	pr_debug("responsible\n");

	/* despite being received via linklayer multicast, this is
	 * actually a unicast IP packet. TCP doesn't like PACKET_MULTICAST */
	skb->pkt_type = PACKET_HOST;

	return XT_CONTINUE;
}