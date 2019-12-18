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
struct udphdr {int dummy; } ;
struct sk_buff {unsigned int len; char* data; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int HZ ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  nf_ct_refresh (struct nf_conn*,struct sk_buff*,int) ; 
 int process_sip_msg (struct sk_buff*,struct nf_conn*,unsigned int,unsigned int,char const**,unsigned int*) ; 
 int sip_timeout ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 unsigned int strlen (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sip_help_udp(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	unsigned int dataoff, datalen;
	const char *dptr;

	/* No Data ? */
	dataoff = protoff + sizeof(struct udphdr);
	if (dataoff >= skb->len)
		return NF_ACCEPT;

	nf_ct_refresh(ct, skb, sip_timeout * HZ);

	if (unlikely(skb_linearize(skb)))
		return NF_DROP;

	dptr = skb->data + dataoff;
	datalen = skb->len - dataoff;
	if (datalen < strlen("SIP/2.0 200"))
		return NF_ACCEPT;

	return process_sip_msg(skb, ct, protoff, dataoff, &dptr, &datalen);
}