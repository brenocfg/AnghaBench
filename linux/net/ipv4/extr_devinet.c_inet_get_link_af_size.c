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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  ip_ptr; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int IPV4_DEVCONF_MAX ; 
 size_t nla_total_size (int) ; 
 struct in_device* rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t inet_get_link_af_size(const struct net_device *dev,
				    u32 ext_filter_mask)
{
	struct in_device *in_dev = rcu_dereference_rtnl(dev->ip_ptr);

	if (!in_dev)
		return 0;

	return nla_total_size(IPV4_DEVCONF_MAX * 4); /* IFLA_INET_CONF */
}