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
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int SKB_GSO_IPXIP6 ; 
 struct sk_buff* inet_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *ip4ip6_gso_segment(struct sk_buff *skb,
					  netdev_features_t features)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP6))
		return ERR_PTR(-EINVAL);

	return inet_gso_segment(skb, features);
}