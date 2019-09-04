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
struct ipt_ECN_info {int ip_ect; } ;
struct iphdr {int tos; int /*<<< orphan*/  check; } ;
typedef  int __u8 ;

/* Variables and functions */
 int IPT_ECN_IP_MASK ; 
 int /*<<< orphan*/  csum_replace2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 

__attribute__((used)) static inline bool
set_ect_ip(struct sk_buff *skb, const struct ipt_ECN_info *einfo)
{
	struct iphdr *iph = ip_hdr(skb);

	if ((iph->tos & IPT_ECN_IP_MASK) != (einfo->ip_ect & IPT_ECN_IP_MASK)) {
		__u8 oldtos;
		if (!skb_make_writable(skb, sizeof(struct iphdr)))
			return false;
		iph = ip_hdr(skb);
		oldtos = iph->tos;
		iph->tos &= ~IPT_ECN_IP_MASK;
		iph->tos |= (einfo->ip_ect & IPT_ECN_IP_MASK);
		csum_replace2(&iph->check, htons(oldtos), htons(iph->tos));
	}
	return true;
}