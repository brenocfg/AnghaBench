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
struct nf_hook_state {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_SEQ_ADJUST_BIT ; 
 int IP_CT_RELATED_REPLY ; 
 int /*<<< orphan*/  NF_CT_STAT_INC_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  drop ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 unsigned int nf_conntrack_confirm (struct sk_buff*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_seq_adjust (struct sk_buff*,struct nf_conn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_is_loopback_packet (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ipv4_confirm(void *priv,
				 struct sk_buff *skb,
				 const struct nf_hook_state *state)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || ctinfo == IP_CT_RELATED_REPLY)
		goto out;

	/* adjust seqs for loopback traffic only in outgoing direction */
	if (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_is_loopback_packet(skb)) {
		if (!nf_ct_seq_adjust(skb, ct, ctinfo, ip_hdrlen(skb))) {
			NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), drop);
			return NF_DROP;
		}
	}
out:
	/* We've seen it coming out the other side: confirm it */
	return nf_conntrack_confirm(skb);
}