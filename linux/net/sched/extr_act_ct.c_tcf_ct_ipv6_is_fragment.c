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
struct sk_buff {unsigned int len; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTO ; 
 unsigned int IP6_FH_F_FRAG ; 
 int ipv6_find_hdr (struct sk_buff*,unsigned int*,int,unsigned short*,unsigned int*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_ct_ipv6_is_fragment(struct sk_buff *skb, bool *frag)
{
	unsigned int flags = 0, len, payload_ofs = 0;
	unsigned short frag_off;
	int nexthdr;

	len =  skb_network_offset(skb) + sizeof(struct ipv6hdr);
	if (unlikely(skb->len < len))
		return -EINVAL;
	if (unlikely(!pskb_may_pull(skb, len)))
		return -ENOMEM;

	nexthdr = ipv6_find_hdr(skb, &payload_ofs, -1, &frag_off, &flags);
	if (unlikely(nexthdr < 0))
		return -EPROTO;

	*frag = flags & IP6_FH_F_FRAG;
	return 0;
}