#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_conntrack_helper {int (* help ) (struct sk_buff*,unsigned int,struct nf_conn*,int) ;} ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_SEQ_ADJUST_BIT ; 
 int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_STAT_INC_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  drop ; 
 unsigned int nf_conntrack_confirm (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_seq_adjust (struct sk_buff*,struct nf_conn*,int,unsigned int) ; 
 int /*<<< orphan*/  nf_is_loopback_packet (struct sk_buff*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 struct nf_conntrack_helper* rcu_dereference (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,unsigned int,struct nf_conn*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned int nf_confirm(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	const struct nf_conn_help *help;

	help = nfct_help(ct);
	if (help) {
		const struct nf_conntrack_helper *helper;
		int ret;

		/* rcu_read_lock()ed by nf_hook_thresh */
		helper = rcu_dereference(help->helper);
		if (helper) {
			ret = helper->help(skb,
					   protoff,
					   ct, ctinfo);
			if (ret != NF_ACCEPT)
				return ret;
		}
	}

	if (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_is_loopback_packet(skb)) {
		if (!nf_ct_seq_adjust(skb, ct, ctinfo, protoff)) {
			NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), drop);
			return NF_DROP;
		}
	}

	/* We've seen it coming out the other side: confirm it */
	return nf_conntrack_confirm(skb);
}