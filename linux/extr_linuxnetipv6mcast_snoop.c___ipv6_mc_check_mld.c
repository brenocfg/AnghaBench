#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mld_msg {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_mc_check_mld_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_mc_validate_checksum ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 struct sk_buff* skb_checksum_trimmed (struct sk_buff*,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int __ipv6_mc_check_mld(struct sk_buff *skb,
			       struct sk_buff **skb_trimmed)

{
	struct sk_buff *skb_chk = NULL;
	unsigned int transport_len;
	unsigned int len = skb_transport_offset(skb) + sizeof(struct mld_msg);
	int ret = -EINVAL;

	transport_len = ntohs(ipv6_hdr(skb)->payload_len);
	transport_len -= skb_transport_offset(skb) - sizeof(struct ipv6hdr);

	skb_chk = skb_checksum_trimmed(skb, transport_len,
				       ipv6_mc_validate_checksum);
	if (!skb_chk)
		goto err;

	if (!pskb_may_pull(skb_chk, len))
		goto err;

	ret = ipv6_mc_check_mld_msg(skb_chk);
	if (ret)
		goto err;

	if (skb_trimmed)
		*skb_trimmed = skb_chk;
	/* free now unneeded clone */
	else if (skb_chk != skb)
		kfree_skb(skb_chk);

	ret = 0;

err:
	if (ret && skb_chk && skb_chk != skb)
		kfree_skb(skb_chk);

	return ret;
}