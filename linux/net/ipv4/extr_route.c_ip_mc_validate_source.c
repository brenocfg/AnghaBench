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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
struct in_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  IN_DEV_ROUTE_LOCALNET (struct in_device*) ; 
 scalar_t__ IPPROTO_IGMP ; 
 int fib_validate_source (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,struct in_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipv4_is_lbcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 

int ip_mc_validate_source(struct sk_buff *skb, __be32 daddr, __be32 saddr,
			  u8 tos, struct net_device *dev,
			  struct in_device *in_dev, u32 *itag)
{
	int err;

	/* Primary sanity checks. */
	if (!in_dev)
		return -EINVAL;

	if (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    skb->protocol != htons(ETH_P_IP))
		return -EINVAL;

	if (ipv4_is_loopback(saddr) && !IN_DEV_ROUTE_LOCALNET(in_dev))
		return -EINVAL;

	if (ipv4_is_zeronet(saddr)) {
		if (!ipv4_is_local_multicast(daddr) &&
		    ip_hdr(skb)->protocol != IPPROTO_IGMP)
			return -EINVAL;
	} else {
		err = fib_validate_source(skb, saddr, 0, tos, 0, dev,
					  in_dev, itag);
		if (err < 0)
			return err;
	}
	return 0;
}