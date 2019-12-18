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
struct sk_buff {int len; } ;
struct iphdr {int ihl; int version; int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int skb_network_offset (struct sk_buff const*) ; 

__attribute__((used)) static int nf_ct_br_ip_check(const struct sk_buff *skb)
{
	const struct iphdr *iph;
	int nhoff, len;

	nhoff = skb_network_offset(skb);
	iph = ip_hdr(skb);
	if (iph->ihl < 5 ||
	    iph->version != 4)
		return -1;

	len = ntohs(iph->tot_len);
	if (skb->len < nhoff + len ||
	    len < (iph->ihl * 4))
                return -1;

	return 0;
}