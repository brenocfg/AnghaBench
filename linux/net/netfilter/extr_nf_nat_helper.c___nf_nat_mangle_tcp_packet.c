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
struct tcphdr {int doff; int /*<<< orphan*/  seq; int /*<<< orphan*/  check; } ;
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  enlarge_skb (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  mangle_contents (struct sk_buff*,unsigned int,unsigned int,unsigned int,char const*,unsigned int) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_seqadj_set (struct nf_conn*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_nat_csum_recalc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcphdr*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 
 unsigned int skb_tailroom (struct sk_buff*) ; 

bool __nf_nat_mangle_tcp_packet(struct sk_buff *skb,
				struct nf_conn *ct,
				enum ip_conntrack_info ctinfo,
				unsigned int protoff,
				unsigned int match_offset,
				unsigned int match_len,
				const char *rep_buffer,
				unsigned int rep_len, bool adjust)
{
	struct tcphdr *tcph;
	int oldlen, datalen;

	if (skb_ensure_writable(skb, skb->len))
		return false;

	if (rep_len > match_len &&
	    rep_len - match_len > skb_tailroom(skb) &&
	    !enlarge_skb(skb, rep_len - match_len))
		return false;

	tcph = (void *)skb->data + protoff;

	oldlen = skb->len - protoff;
	mangle_contents(skb, protoff + tcph->doff*4,
			match_offset, match_len, rep_buffer, rep_len);

	datalen = skb->len - protoff;

	nf_nat_csum_recalc(skb, nf_ct_l3num(ct), IPPROTO_TCP,
			   tcph, &tcph->check, datalen, oldlen);

	if (adjust && rep_len != match_len)
		nf_ct_seqadj_set(ct, ctinfo, tcph->seq,
				 (int)rep_len - (int)match_len);

	return true;
}