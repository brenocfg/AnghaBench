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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_saddr_score {int dummy; } ;
struct ipv6_saddr_dst {int dummy; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 struct inet6_dev* __in6_dev_get (struct net_device const*) ; 
 int __ipv6_dev_get_saddr (struct net*,struct ipv6_saddr_dst*,struct inet6_dev*,struct ipv6_saddr_score*,int) ; 

__attribute__((used)) static int ipv6_get_saddr_master(struct net *net,
				 const struct net_device *dst_dev,
				 const struct net_device *master,
				 struct ipv6_saddr_dst *dst,
				 struct ipv6_saddr_score *scores,
				 int hiscore_idx)
{
	struct inet6_dev *idev;

	idev = __in6_dev_get(dst_dev);
	if (idev)
		hiscore_idx = __ipv6_dev_get_saddr(net, dst, idev,
						   scores, hiscore_idx);

	idev = __in6_dev_get(master);
	if (idev)
		hiscore_idx = __ipv6_dev_get_saddr(net, dst, idev,
						   scores, hiscore_idx);

	return hiscore_idx;
}