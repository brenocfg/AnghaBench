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
struct igmphdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ip_mc_may_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ip_mc_validate_checksum ; 
 unsigned int ip_transport_len (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_checksum_trimmed (struct sk_buff*,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int ip_mc_check_igmp_csum(struct sk_buff *skb)
{
	unsigned int len = skb_transport_offset(skb) + sizeof(struct igmphdr);
	unsigned int transport_len = ip_transport_len(skb);
	struct sk_buff *skb_chk;

	if (!ip_mc_may_pull(skb, len))
		return -EINVAL;

	skb_chk = skb_checksum_trimmed(skb, transport_len,
				       ip_mc_validate_checksum);
	if (!skb_chk)
		return -EINVAL;

	if (skb_chk != skb)
		kfree_skb(skb_chk);

	return 0;
}