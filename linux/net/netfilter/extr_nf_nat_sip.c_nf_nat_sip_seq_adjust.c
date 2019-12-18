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
struct tcphdr {int /*<<< orphan*/  seq; } ;
struct sk_buff {scalar_t__ data; } ;
struct nf_conn {int dummy; } ;
typedef  scalar_t__ s16 ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_seqadj_set (struct nf_conn*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nf_nat_sip_seq_adjust(struct sk_buff *skb, unsigned int protoff,
				  s16 off)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	const struct tcphdr *th;

	if (nf_ct_protonum(ct) != IPPROTO_TCP || off == 0)
		return;

	th = (struct tcphdr *)(skb->data + protoff);
	nf_ct_seqadj_set(ct, ctinfo, th->seq, off);
}